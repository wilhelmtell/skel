#ifndef SKELETON_INSTANTIATION_ERROR_HH_
#define SKELETON_INSTANTIATION_ERROR_HH_

#include <stdexcept>
#include <string>

namespace skel {
struct skeleton_instantiation_error : public std::runtime_error {
    skeleton_instantiation_error(std::string const& m) : std::runtime_error(m) { }
};
}  // namespace skel

#endif  // SKELETON_INSTANTIATION_ERROR_HH_
