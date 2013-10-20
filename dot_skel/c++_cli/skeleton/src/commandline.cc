#include "commandline.hh"
#include "verify.hh"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;

namespace {APPNAME} \{
po::options_description options_description()
\{
    po::options_description desc;
    desc.add_options()
        ("help", "display this help message");
    return desc;
\}

po::variables_map variables_map(int argc, char const * argv[],
                                po::options_description const& desc)
\{
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);
    return vm;
\}

void exec(po::variables_map const& vm)
\{
    {APPNAME}::verify(vm);
    auto const help(vm.count("help") ? 42 : 0);
    foo(help);
\}
\}  // namespace {APPNAME}
