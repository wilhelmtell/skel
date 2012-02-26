#ifndef ERROR_HH_
#define ERROR_HH_

#include <stdexcept>

namespace skel {
struct skeleton_syntax_error : std::runtime_error {
    skeleton_syntax_error() : std::runtime_error("") { }
};
}  // namespace skel

#endif  // ERROR_HH_

