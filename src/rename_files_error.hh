#ifndef RENAME_FILES_ERROR_HH_
#define RENAME_FILES_ERROR_HH_

#include <stdexcept>
#include <string>

namespace skel {
struct rename_files_error : std::runtime_error {
    rename_files_error(std::string const& m) : std::runtime_error(m) { }
};
}  // namespace skel

#endif  // RENAME_FILES_ERROR_HH_
