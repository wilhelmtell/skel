#ifndef INSTANTIATE_SKELETON_ERROR_HH_
#define INSTANTIATE_SKELETON_ERROR_HH_

#include <stdexcept>
#include <string>

namespace skel {
struct file_open_error : public std::runtime_error {
    file_open_error(std::string const& m) : std::runtime_error(m) { }
};

struct stream_error : public std::runtime_error {
    stream_error(std::string const& m) : std::runtime_error(m) { }
};
}  // namespace skel

#endif  // INSTANTIATE_SKELETON_ERROR_HH_
