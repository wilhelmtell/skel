#include <iostream>
#include <boost/program_options.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include "config.hh"
#include "skeleton.hh"
#include "list_skeletons.hh"
#include <map>
#include <fstream>
#include "load_substitutions_map.hh"
#include "error.hh"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    std::string const usage(" Usage: skel [options] [--skeleton=]<skeleton>");
    po::options_description desc("Options");
    desc.add_options()
        ("help", "display this help message")
        ("list-skeletons", "list skeletons avilable for --skeleton")
        ("map-file", po::value<std::string>(), "macro-substitution map file")
        ("skeleton",
         po::value<std::vector<std::string>>()->required(),
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
            TEMPLOG_LOG(skel::log_user,templog::sev_error,templog::aud_user)
                << "required option --skeleton missing";
            std::cerr << "please specify a skeleton to instantiate.\n";
            return 1;
        }
    }

    try {
        if( vm.count("help") ) {
            std::cout << usage << "\n\n" << desc;
            return 0;
        }
        if( vm.count("list-skeletons") ) {
            skel::list_skeletons();
            return 0;
        }
        if( vm.count("skeleton") ) {
            auto skeleton_names(vm["skeleton"].as<std::vector<std::string>>());
            std::map<std::string,std::string> subs;
            if( vm.count("map-file") ) {
                std::ifstream subs_file(vm["map-file"].as<std::string>());
                skel::load_substitutions_map(subs_file, subs);
            }
            return ! skel::instantiate_skeletons(skeleton_names.begin(),
                                                 skeleton_names.end(),
                                                 subs);
        }
    } catch( skel::skeleton_syntax_error const& e ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_error,templog::aud_developer)
            << "skeleton syntax error.";
        return 1;
    } catch( std::runtime_error const& e ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_error,templog::aud_developer)
            << e.what();
        return 1;
    } catch( std::logic_error const& e ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_fatal,templog::aud_developer)
            << "logic_error: " << e.what();
        return 1;
    } catch( ... ) {
        TEMPLOG_LOG(skel::log_developer,templog::sev_error,templog::aud_developer)
            << "unknown error. will you be so kind as to send me an email with "
            "step-by-step instructions on how to reproduce this error? i'd "
            "love to fix it! my email address is " << skel::AUTHOR_EMAIL << '.';
    }
    return 0;
}
