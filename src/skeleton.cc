#include "skeleton.hh"
#include "config.hh"
#include <templog/logging.h>
#include <string>
#include <unistd.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>

namespace fs = boost::filesystem3;

namespace skel {
skeleton::skeleton(std::string const& name)
: name(name)
{
}

void skeleton::instantiate() const
{
    TEMPLOG_LOG(log_developer,templog::sev_info,templog::aud_developer)
        << "instantiating skeleton " << name;
    const fs::path HOME(getenv("HOME"));
    const fs::path USER_RC_DIR(HOME / RC_DIR);
    const fs::path SKELETON_DIR(USER_RC_DIR / name);
    fs::copy(SKELETON_DIR, ".");
}

bool skeleton_installed(std::string const& name)
{
    const fs::path HOME(getenv("HOME"));
    const fs::path USER_RC_DIR(HOME / RC_DIR);
    return fs::is_directory(USER_RC_DIR / name);
}
}  // namespace skel
