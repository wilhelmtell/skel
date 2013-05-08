#ifndef {APPNAME}_COMMANDLINE_HH_
#define {APPNAME}_COMMANDLINE_HH_

#include <boost/program_options.hpp>

namespace {APPNAME} \{
boost::program_options::options_description options_description();

boost::program_options::variables_map
variables_map(int argc, char const * argv[],
              boost::program_options::options_description const& desc);

void exec(boost::program_options::variables_map const& vm);
\}  // namespace {APPNAME}

#endif  // {APPNAME}_COMMANDLINE_HH_
