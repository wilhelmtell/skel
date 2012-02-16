#include <iostream>
#include <boost/program_options.hpp>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include "config.hh"
#include "skeleton.hh"
#include <boost/filesystem/operations.hpp>
#include <iterator>

namespace po = boost::program_options;
namespace fs = boost::filesystem3;

template<typename In, typename Out, typename Op, typename Pred>
Out transform_if(In first, In last, Out out, Op op, Pred pred)
{
    while( first != last ) {
        if( pred(*first) ) *out++ = op(*first);
        ++first;
    }
    return out;
}

void list_skeletons()
{
    std::ostream& out = std::cout;
    transform_if(fs::directory_iterator(fs::path(getenv("HOME")) / skel::RC_DIR),
                 fs::directory_iterator(),
                 std::ostream_iterator<std::string>(out, "\n"),
                 [](fs::directory_entry const& ent) {
                     return ent.path().filename().string();
                 },
                 [](fs::directory_entry const& ent) {
                     return fs::is_directory(ent.path());
                 });
    out << '\n';
}

// first and last are iterators over a sequence of skeleton names (strings)
template<typename In>
bool instantiate_skeletons(In first, In last)
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
        ("list-skeletons", "List skeletons avilable for --skeleton")
        ("skeleton",
         po::value<std::vector<std::string>>(),
         "Skeleton to instantiate");
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
        if( vm.count("list-skeletons") ) {
            list_skeletons();
            return 0;
        }
        if( vm.count("skeleton") ) {
            auto skeleton_names(vm["skeleton"].as<std::vector<std::string>>());
            return ! instantiate_skeletons(std::begin(skeleton_names),
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
            << "unknown error. will you be so kind as to send me an email with "
            "step-by-step instructions on how to reproduce this error? my "
            "email address is " << skel::AUTHOR_EMAIL;
    }
    return 0;
}
