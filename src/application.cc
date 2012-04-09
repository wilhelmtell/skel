#include "application.hh"
#include <vector>
#include <memory>
#include <boost/program_options.hpp>
#include <sstream>
#include <string>
#include "print_message.hh"
#include "expand_macros.hh"
#include "instantiate_skeleton.hh"
#include "memory.hh"
#include "mapping.hh"
#include <algorithm>
#include <iterator>
#include <utility>
#include <map>

namespace po = boost::program_options;

namespace {
std::vector<std::unique_ptr<skel::command>>
create_commands(po::options_description const& desc, po::variables_map const& conf)
{
    std::vector<std::unique_ptr<skel::command>> commands;
    if( conf.count("help") ) {
        std::ostringstream ss;
        ss << " Usage: skel [options] [--skeleton=]<skeleton>\n\n" << desc;
        commands.push_back(mn::make_unique<skel::print_message>(ss.str()));
    }
    if( conf.count("skeleton") ) {
        auto const skeleton = conf["skeleton"].as<std::string>();
        commands.push_back(mn::make_unique<skel::instantiate_skeleton>(skeleton));
    }
    if( conf.count("substitute") ) {
        auto const maps_from_cmdline = conf["substitute"].as<std::vector<skel::mapping>>();
        std::map<std::string,std::string> substitutions;
        std::transform(maps_from_cmdline.begin(), maps_from_cmdline.end(),
                       std::inserter(substitutions, substitutions.end()),
                       [&](skel::mapping const& m) {
                           return std::make_pair(m.from, m.to);
                       });
        commands.push_back(mn::make_unique<skel::expand_macros>(substitutions));
    }
    return commands;
}

std::vector<std::unique_ptr<skel::command>> parse_commandline(int argc, char * argv[])
{
    po::options_description desc("Options");
    desc.add_options()
        ("help", "display this help message")
        ("substitute",
         po::value<std::vector<skel::mapping>>(),
         "define a substitution mapping")
        ("skeleton", po::value<std::string>(), "pick skeleton to instantiate");
    po::positional_options_description positional;
    positional.add("skeleton", -1);
    po::variables_map conf;
    po::store(po::command_line_parser(argc, argv)
              .options(desc)
              .positional(positional)
              .run(), conf);
    po::notify(conf);
    return create_commands(desc, conf);
}
}

namespace skel {
application::application(int argc, char *argv[])
: commands(parse_commandline(argc, argv))
{
}

void application::exec() const {
    for( auto const& c : commands )
        (*c)();
}
}  // namespace skel
