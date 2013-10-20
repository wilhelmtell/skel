#ifndef {APPNAME}_VERIFY_ERROR_HH_
#define {APPNAME}_VERIFY_ERROR_HH_

#include <stdexcept>

namespace {APPNAME} \{
struct some_error : std::runtime_error \{
    some_error() : runtime_error("no source files specified")
\};
\}  // namespace {APPNAME}

#endif  // {APPNAME}_VERIFY_ERROR_HH_
