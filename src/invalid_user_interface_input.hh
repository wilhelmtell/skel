#ifndef INVALID_USER_INTERFACE_INPUT_HH_
#define INVALID_USER_INTERFACE_INPUT_HH_

#include <stdexcept>

namespace skel {
struct invalid_user_interface_input : public std::runtime_error {
    invalid_user_interface_input() : std::runtime_error("") { }
};
}  // namespace skel

#endif  // INVALID_USER_INTERFACE_INPUT_HH_
