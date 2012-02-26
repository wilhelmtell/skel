#include "skeleton.hh"
#include "config.hh"
#include "personalize_skeleton.hh"
#include <templog/logging.h>
#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>

namespace fs = boost::filesystem3;

namespace {
struct copy_part {
    copy_part(fs::path const& from, fs::path const& to);
    copy_part(copy_part const&) = delete;
    copy_part& operator=(copy_part const&) = delete;
    copy_part(copy_part&& rhs);
    ~copy_part();

    void commit();

private:
    bool owning;
    std::string to;  // HACK: should be an fs::path, but fs::path isn't moveable
};

copy_part::copy_part(fs::path const& from, fs::path const& to)
: owning(true)
, to(to.string())
{
    TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
        << "copying " << from.string();
    fs::copy(from, to);
}

copy_part::copy_part(copy_part&& rhs)
: owning(false)
, to()
{
    std::swap(rhs.owning, owning);
    std::swap(rhs.to, to);
}

void copy_part::commit()
{
    owning = false;
}

copy_part::~copy_part()
{
    if( owning ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "removing " << to << " ...";
        boost::system::error_code e;
        fs::remove(to, e);
    }
}


struct instantiate_part {
    instantiate_part(fs::path const& from, fs::path const& to,
                     std::map<std::string,std::string> const& subs);

    void commit();

private:
    copy_part cp;
    std::map<std::string,std::string> const& subs;
};

instantiate_part::instantiate_part(fs::path const& from, fs::path const& to,
                                   std::map<std::string,std::string> const& subs)
: cp(from, to)
, subs(subs)
{
    if( fs::is_regular_file(to) ) {
        fs::path temp_out(to.string() + ".out");
        skel::personalize_skeleton(to, temp_out, subs);
        fs::rename(temp_out, to);
    }
}

void instantiate_part::commit()
{
    cp.commit();
}


struct instantiate_parts {
    instantiate_parts();
    instantiate_parts(instantiate_parts const&) = delete;
    instantiate_parts& operator=(instantiate_parts const&) = delete;
    instantiate_parts(instantiate_parts&&) = default;
    ~instantiate_parts();

    void commit();
    void add(instantiate_part p);

private:
    bool committed;
    std::stack<instantiate_part> parts;
};

instantiate_parts::instantiate_parts()
: committed(false)
{
}

instantiate_parts::~instantiate_parts()
{
    if( ! committed ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "copy failed; rolling back ...";
        while( ! parts.empty() )
            parts.pop();
    }
}

void instantiate_parts::commit()
{
    committed = true;
    while( ! parts.empty() ) {
        parts.top().commit();
        parts.pop();
    }
}

void instantiate_parts::add(instantiate_part p)
{
    parts.push(std::move(p));
}

void copy_r(fs::path const& from, fs::path const& to,
            std::map<std::string,std::string> const& subs)
{
    auto const from_parent = from.parent_path();
    auto const parent_path_length = std::distance(from_parent.begin(),
                                                  from_parent.end());
    instantiate_parts parts;
    std::for_each(fs::recursive_directory_iterator(from),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        auto const current = ent.path();
        auto const relative_pos = std::next(current.begin(),
                                            parent_path_length + 1);
        auto const current_to = std::accumulate(relative_pos, current.end(),
                                                to, std::divides<fs::path>());
        parts.add(instantiate_part(current, current_to, subs));
    });
    parts.commit();
}
}  // namespace

namespace skel {
skeleton::skeleton(std::string const& name,
                   std::map<std::string,std::string> const& subs)
: name(name)
, subs(subs)
{
}

void skeleton::instantiate() const
{
    TEMPLOG_LOG(log_developer,templog::sev_info,templog::aud_developer)
        << "instantiating skeleton " << name << " ...";
    copy_r(fs::path(USER_HOME) / RC_DIR / name, fs::current_path(), subs);
}

bool skeleton_installed(std::string const& name)
{
    return fs::is_directory(fs::path(USER_HOME) / RC_DIR / name);
}
}  // namespace skel
