#include <iostream>
#include "parser.hh"
#include <string>
#include <map>
#include <boost/program_options.hpp>
#include "mapping.hh"
#include <vector>
#include "program_options.hh"

namespace po = boost::program_options;

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
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .positional(positional)
                  .run(), vm);
        po::notify(vm);
    } catch( po::required_option const& e ) {
        if( ! vm.count("help") && ! vm.count("list-skeletons") ) {
            std::cerr << "please specify a skeleton to instantiate.\n";
            return 1;
        }
    }

    try {
        if( vm.count("help") ) {
            std::cout << usage << "\n\n" << desc;
            return 0;
        }
        std::map<std::string,std::string> substitutions;
        skel::parse(std::cin, std::cout, substitutions);
    } catch( skel::syntax_error const& e ) {
        std::cerr << "skeleton syntax error.\n";
        return 1;
    } catch( std::runtime_error const& e ) {
        std::cerr << "runtime error: " << e.what() << '\n';
        return 1;
    } catch( std::logic_error const& e ) {
        std::cerr << "logic error: " << e.what() << '\n';
        return 1;
    } catch( ... ) {
        std::cerr << "unknown error. will you be so kind and send me an email "
            "with step-by-step instructions on how to reproduce this error? "
            "i'd love to fix it, but i need to know about it first. my email "
            "address is matan.nassau@gmail.com.\n";
    }
    return 0;
}
