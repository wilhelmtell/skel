#ifndef HELPERS_HH_
#define HELPERS_HH_

#include <string>

namespace skel { struct application; }

skel::application make_application(std::string const& cmdline_args);

#endif  // HELPERS_HH_
