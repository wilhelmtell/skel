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

namespace po = boost::program_options;

namespace {
void exec(po::variables_map const& conf)
{
    std::map<std::string,std::string> substitutions;
    auto maps_from_cmdline = conf["map"].as<std::vector<skel::mapping>>();
    std::transform(maps_from_cmdline.begin(), maps_from_cmdline.end(),
                   std::inserter(substitutions, substitutions.end()),
                   [&](skel::mapping const& m) {
                       return std::make_pair(m.from, m.to);
                   });
    skel::parse(std::cin, std::cout, substitutions);
}
}

namespace skel {
application::application(int argc, char *argv[])
{
    std::string const usage(" Usage: skel [options] [--skeleton=]<skeleton>");
    po::options_description desc("Options");
    desc.add_options()
        ("help", "display this help message")
        ("map", po::value<std::vector<skel::mapping>>(), "define a substitution mapping")
        ("skeleton",
         po::value<std::string>()->required(),
         "pick skeleton to instantiate");
    po::positional_options_description positional;
    positional.add("skeleton", -1);
    po::variables_map conf;
    try {
        po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .positional(positional)
                  .run(), conf);
        po::notify(conf);
    } catch( po::required_option const& e ) {
        if( conf.count("help") )
            std::cout << usage << "\n\n" << desc;
        throw;
    }
    exec(conf);
}
}  // namespace skel
