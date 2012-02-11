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
#include "utility.hh"

namespace fs = boost::filesystem3;

namespace skel {
skeleton::skeleton(std::string const& name)
: name(name)
{
}

void skeleton::instantiate() const
{
    TEMPLOG_LOG(log_developer,templog::sev_info,templog::aud_developer)
        << "instantiating skeleton " << name << " ...";
    skel::copy_r(fs::path(getenv("HOME")) / RC_DIR / name, fs::current_path());
}

bool skeleton_installed(std::string const& name)
{
    return fs::is_directory(fs::path(getenv("HOME")) / RC_DIR / name);
}
}  // namespace skel
