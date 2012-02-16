#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <templog/logging.h>
#include <cstdlib>

namespace skel {
char const * const AUTHOR_EMAIL = "matan.nassau@gmail.com";
typedef templog::logger< templog::global_logger
                       , templog::sev_debug
                       , templog::audience_list<templog::aud_developer> >
                       log_developer;
typedef templog::logger< templog::global_logger
                       , templog::sev_message
                       , templog::audience_list<templog::aud_user> >
                       log_user;
char const * const RC_DIR = ".skel";
char const * const USER_HOME = std::getenv("HOME");
}  // namespace skel

#endif  // CONFIG_HH_
