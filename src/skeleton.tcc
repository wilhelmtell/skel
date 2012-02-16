#ifndef SKELETON_TCC_
#define SKELETON_TCC_

#include "skeleton.hh"
#include "config.hh"
#include <templog/logging.h>
#include <algorithm>

namespace skel {
template<typename In>
bool instantiate_skeletons(In first, In last)
{
    auto const installed_end = std::partition(first, last,
                                              skeleton_installed);
    if( installed_end != last ) {
        std::for_each(installed_end, last, [](std::string const& name) {
            TEMPLOG_LOG(log_user,templog::sev_error,templog::aud_user)
                << "skeleton " << name << " not found";
        });
        return false;
    }
    std::for_each(first, last, [](std::string const& name) {
        skeleton(name).instantiate();
    });
    return true;
}
}  // namespace skel

#endif  // SKELETON_TCC_
