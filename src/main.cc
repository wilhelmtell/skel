#include <iostream>
#include "parser.hh"
#include <string>
#include <map>
#include <boost/program_options.hpp>
#include "mapping.hh"
#include <vector>
#include <algorithm>
#include <utility>

namespace po = boost::program_options;

namespace {
bool exec(po::variables_map const& conf)
{
    try {
        std::map<std::string,std::string> substitutions;
        auto maps_from_cmdline = conf["map"].as<std::vector<skel::mapping>>();
        std::transform(maps_from_cmdline.begin(), maps_from_cmdline.end(),
                       std::inserter(substitutions, substitutions.end()),
                       [&](skel::mapping const& m) {
                           return std::make_pair(m.from, m.to);
                       });
        skel::parse(std::cin, std::cout, substitutions);
    } catch( skel::syntax_error const& e ) {
        std::cerr << "skeleton syntax error.\n";
        return false;
    } catch( std::runtime_error const& e ) {
        std::cerr << "runtime error: " << e.what() << '\n';
        return false;
    } catch( std::logic_error const& e ) {
        std::cerr << "logic error: " << e.what() << '\n';
        return false;
    } catch( ... ) {
        std::cerr << "unknown error. will you be so kind and send me an email "
            "with step-by-step instructions on how to reproduce this error? "
            "i'd love to fix it, but i need to know about it first. my email "
            "address is matan.nassau@gmail.com.\n";
    }
    return true;
}
}

int main(int argc, char* argv[])
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
        if( conf.count("help") ) {
            return ! (std::cout << usage << "\n\n" << desc);
        } else if( ! conf.count("list-skeletons") ) {
            std::cerr << "please specify a skeleton to instantiate.\n";
            return 1;
        }
    }
    return ! exec(conf);
}
