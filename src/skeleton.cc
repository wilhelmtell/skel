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

struct raii_chdir {
    raii_chdir(fs::path const& p);
    ~raii_chdir();
private:
    fs::path orig;
};

raii_chdir::raii_chdir(fs::path const& p)
: orig(fs::current_path())
{
    TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
        << "chdir " << p.string();
    fs::current_path(p);
}

raii_chdir::~raii_chdir()
{
    TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
        << "chdir " << orig.string();
    fs::current_path(orig);
}

void copy_r(fs::path const& from)
{
    auto original_cwd(fs::current_path());
    raii_chdir temporarily_chdir(fs::path(getenv("HOME")) / skel::RC_DIR);
    std::for_each(fs::recursive_directory_iterator(from),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "copying " << ent.path().string();
        fs::copy(ent.path(), original_cwd / ent.path());
    });
}

namespace skel {
skeleton::skeleton(std::string const& name)
: name(name)
{
}

void skeleton::instantiate() const
{
    TEMPLOG_LOG(log_developer,templog::sev_info,templog::aud_developer)
        << "instantiating skeleton " << name << " ...";
    // fs::copy(fs::path(getenv("HOME")) / RC_DIR / name, name);
    // copy_r(name);
    auto const ABS_RC_DIR = fs::path(getenv("HOME")) / RC_DIR;
    fs::path const SKELETON_DIR(ABS_RC_DIR / name);
    std::for_each(fs::recursive_directory_iterator(SKELETON_DIR),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "copying " << ent.path().string();
        auto const current = ent.path();
        auto const relative_pos = std::next(current.begin(),
                                            std::distance(ABS_RC_DIR.begin(),
                                                          ABS_RC_DIR.end()) + 1);
        auto const p = std::accumulate(relative_pos, current.end(),
                                       fs::path(), std::divides<fs::path>());
        fs::copy(current, p);
    });
}

bool skeleton_installed(std::string const& name)
{
    return fs::is_directory(fs::path(getenv("HOME")) / RC_DIR / name);
}
}  // namespace skel
