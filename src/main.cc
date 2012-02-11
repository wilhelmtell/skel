#include <iostream>
#include <boost/program_options.hpp>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include "config.hh"
#include "skeleton.hh"

namespace po = boost::program_options;

template<typename In>
bool instantiate_skeleton_names(In first, In last)
{
    auto const installed_end = std::partition(first, last,
                                              skel::skeleton_installed);
    if( installed_end != last ) {
        std::for_each(installed_end, last, [](std::string const& name) {
            TEMPLOG_LOG(skel::log_user,templog::sev_error,templog::aud_user)
                << "skeleton " << name << " not found";
        });
        return false;
    }
    std::for_each(first, last, [](std::string const& name) {
        skel::skeleton(name).instantiate();
    });
    return true;
}

int main(int argc, char* argv[])
{
    std::string const usage(" Usage: skel [options]");
    po::options_description desc("Options");
    desc.add_options()
        ("help", "Display this help message")
        ("skeleton",
         po::value<std::vector<std::string>>(),
         "skeleton to instantiate");
    po::positional_options_description positional;
    positional.add("skeleton", -1);
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .positional(positional)
                  .run(), vm);
        po::notify(vm);
    } catch( po::error const& e ) {
        TEMPLOG_LOG(skel::log_user,templog::sev_error,templog::aud_user)
            << e.what();
        return 1;
    }

    try {
        if( vm.count("help") ) {
            std::cout << usage << "\n\n" << desc;
            return 0;
        }
        if( vm.count("skeleton") ) {
            auto skeleton_names(vm["skeleton"].as<std::vector<std::string>>());
            return ! instantiate_skeleton_names(std::begin(skeleton_names),
                                                std::end(skeleton_names));
        }
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
            << "this is embarrassing: unknown error";
    }
    return 0;
}