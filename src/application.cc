#include "application.hh"
#include <string>
#include <boost/program_options.hpp>
#include <vector>
#include "mapping.hh"
#include <map>
#include <algorithm>
#include "parser.hh"
#include <iterator>
#include <utility>
#include <iostream>
#include <sstream>

namespace po = boost::program_options;

namespace {
bool print_help(po::options_description const& desc, po::variables_map const&)
{
    std::string const usage(" Usage: skel [options] [--skeleton=]<skeleton>");
    return std::cout << usage << "\n\n" << desc;
}

bool help_and_other_options(po::options_description const& desc,
                            po::variables_map const& conf)
{
    std::cout << "Help requested; doing nothing other than help.\n\n";
    return print_help(desc, conf);
}

bool exec(po::options_description const&, po::variables_map const& conf)
{
    std::map<std::string,std::string> substitutions;
    auto maps_from_cmdline = conf["substitute"].as<std::vector<skel::mapping>>();
    std::transform(maps_from_cmdline.begin(), maps_from_cmdline.end(),
                   std::inserter(substitutions, substitutions.end()),
                   [&](skel::mapping const& m) {
                       return std::make_pair(m.from, m.to);
                   });
    std::ostringstream out;
    skel::parse(std::cin, out, substitutions);
    return std::cout << out.str();
}
}

namespace skel {
application::application(int argc, char *argv[])
: desc("Options")
, exec_func(0)
{
    desc.add_options()
        ("help", "display this help message")
        ("substitute", po::value<std::vector<skel::mapping>>(), "define a substitution mapping")
        ("skeleton",
         po::value<std::string>()->required(),
         "pick skeleton to instantiate");
    po::positional_options_description positional;
    positional.add("skeleton", -1);
    try {
        po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .positional(positional)
                  .run(), conf);
        po::notify(conf);
        if( conf.count("help") )
            exec_func = help_and_other_options;
        else
            exec_func = ::exec;
    } catch( po::required_option const& e ) {
        if( conf.count("help") )
            exec_func = print_help;
        else
            throw;
    }
}

bool application::exec() const {
    return exec_func(desc, conf);
}
}  // namespace skel
