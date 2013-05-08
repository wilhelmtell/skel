#ifndef ACP_VERIFY_TCC_
#define ACP_VERIFY_TCC_

#include "verify.hh"
#include "verify_error.hh"

namespace {APPNAME} \{ namespace detail \{
template<typename I>
void verify_help(I const& vm)
\{
    if( ! vm.count("help") )
        throw some_error();
\}
\} \}  // namespace {APPNAME}::detail


namespace {APPNAME} \{
template<typename I>
void verify(I const& vm)
\{
    detail::verify_help(vm);
\}
\}  // namespace {APPNAME}

#endif  // ACP_VERIFY_TCC_
