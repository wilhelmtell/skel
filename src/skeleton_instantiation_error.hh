#ifndef SKELETON_INSTANTIATION_ERROR_HH_
#define SKELETON_INSTANTIATION_ERROR_HH_

#include <stdexcept>

namespace skel {
struct skeleton_instantiation_error : public std::runtime_error {
    skeleton_instantiation_error() : std::runtime_error("") { }
};
}  // namespace skel

#endif  // SKELETON_INSTANTIATION_ERROR_HH_
