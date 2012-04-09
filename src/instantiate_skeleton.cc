#include "instantiate_skeleton.hh"
#include <boost/filesystem.hpp>
#include <boost/system/system_error.hpp>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <functional>
#include <stack>
#include <numeric>

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
        boost::system::error_code e;
        fs::remove(to, e);
    }
}


struct instantiate_part {
    instantiate_part(fs::path const& from, fs::path const& to);

    void commit();

private:
    copy_part cp;
};

instantiate_part::instantiate_part(fs::path const& from, fs::path const& to)
: cp(from, to)
{
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

void copy_r(fs::path const& from, fs::path const& to)
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
        parts.add(instantiate_part(current, current_to));
    });
    parts.commit();
}
}

namespace skel {
instantiate_skeleton::instantiate_skeleton(std::string const& name)
: name(name)
{
}

void instantiate_skeleton::operator()() const
{
    char const * const HOME = std::getenv("HOME");
    char const * const RC_DIR = ".skel";
    char const * const SKELETON_DIR = "skeleton";
    copy_r(fs::path(HOME) / RC_DIR / name / SKELETON_DIR, fs::current_path());
}
}  // namespace skel
