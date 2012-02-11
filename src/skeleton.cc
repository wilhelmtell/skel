#include "skeleton.hh"
#include "config.hh"
#include <templog/logging.h>
#include <string>
#include <unistd.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>
#include <numeric>
#include <functional>

namespace fs = boost::filesystem3;

namespace {
void copy_r(fs::path const& from, fs::path const& to)
{
    auto const from_parent = from.parent_path();
    auto const parent_path_length = std::distance(from_parent.begin(),
                                                  from_parent.end());
    std::for_each(fs::recursive_directory_iterator(from),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "copying " << ent.path().string();
        auto const current = ent.path();
        auto const relative_pos = std::next(current.begin(),
                                            parent_path_length + 1);
        auto const current_to = std::accumulate(relative_pos, current.end(),
                                                to, std::divides<fs::path>());
        fs::copy(current, current_to);
    });
}
}  // namespace

namespace skel {
skeleton::skeleton(std::string const& name)
: name(name)
{
}

void skeleton::instantiate() const
{
    TEMPLOG_LOG(log_developer,templog::sev_info,templog::aud_developer)
        << "instantiating skeleton " << name << " ...";
    copy_r(fs::path(getenv("HOME")) / RC_DIR / name, fs::current_path());
}

bool skeleton_installed(std::string const& name)
{
    return fs::is_directory(fs::path(getenv("HOME")) / RC_DIR / name);
}
}  // namespace skel
