#include "instantiate_skeleton.hh"
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <iterator>
#include <string>
#include <algorithm>
#include <functional>
#include <stack>
#include <numeric>
#include <map>
#include "instantiate_parts.hh"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem3;

namespace skel {
instantiate_skeleton::instantiate_skeleton(std::string const& name,
                                           std::map<std::string,std::string> const& mappings)
: name(name)
, mappings(mappings)
{
}

void instantiate_skeleton::execute()
{
    static char const * const HOME = std::getenv("HOME");
    static char const * const RC_DIR = ".skel";
    static char const * const SKELETON_DIR = "skeleton";
    auto const from = fs::path(HOME) / RC_DIR / name / SKELETON_DIR;
    auto const to = fs::current_path();
    auto const from_parent = from.parent_path();
    auto const parent_path_length = std::distance(from_parent.begin(),
                                                  from_parent.end());
    std::for_each(fs::recursive_directory_iterator(from),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        auto const current = ent.path();
        auto const relative_pos = std::next(current.begin(),
                                            parent_path_length + 1);
        auto const current_to = std::accumulate(relative_pos, current.end(),
                                                to, std::divides<fs::path>());
        parts.add(instantiate_part(current, current_to, mappings));
    });
}

void instantiate_skeleton::commit()
{
    parts.commit();
}
}  // namespace skel
