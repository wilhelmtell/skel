#include "utility.hh"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>
#include <vector>
#include "config.hh"

namespace fs = boost::filesystem3;

namespace {
struct copy_part {
    copy_part(fs::path const& from, fs::path const& to);
    copy_part(copy_part const&) = delete;
    copy_part& operator=(copy_part const&) = delete;
    copy_part(copy_part&&) = default;
    ~copy_part();

    void commit();

private:
    bool committed;
    std::string to;  // HACK: should be an fs::path, but fs::path isn't moveable
};

copy_part::copy_part(fs::path const& from, fs::path const& to)
: committed(false)
, to(to.string())
{
    TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
        << "copying " << from.string();
    fs::copy(from, to);
}

void copy_part::commit()
{
    committed = true;
}

copy_part::~copy_part()
{
    if( ! committed ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "removing " << to << " ...";
        boost::system::error_code e;
        fs::remove(to, e);
    }
}

struct copy_parts {
    copy_parts();
    copy_parts(copy_parts const&) = delete;
    copy_parts& operator=(copy_parts const&) = delete;
    copy_parts(copy_parts&&) = default;
    ~copy_parts();

    void commit();
    void add(copy_part p);

private:
    bool committed;
    std::vector<copy_part> stack;
};

copy_parts::copy_parts()
: committed(false)
{
}

copy_parts::~copy_parts()
{
    if( ! committed ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "copy failed; rolling back ...";
        while( ! stack.empty() )
            stack.pop_back();
    }
}

void copy_parts::commit()
{
    committed = true;
    while( ! stack.empty() ) {
        stack.back().commit();
        stack.pop_back();
    }
}

void copy_parts::add(copy_part p)
{
    stack.push_back(std::move(p));
}
}  // namespace

namespace skel {
void copy_r(fs::path const& from, fs::path const& to)
{
    auto const from_parent = from.parent_path();
    auto const parent_path_length = std::distance(from_parent.begin(),
                                                  from_parent.end());
    copy_parts parts;
    std::for_each(fs::recursive_directory_iterator(from),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        auto const current = ent.path();
        auto const relative_pos = std::next(current.begin(),
                                            parent_path_length + 1);
        auto const current_to = std::accumulate(relative_pos, current.end(),
                                                to, std::divides<fs::path>());
        parts.add(copy_part(current, current_to));
    });
    parts.commit();
}
}  // namespace skel
