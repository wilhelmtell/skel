#include "application.hh"
#include <vector>
#include <boost/program_options.hpp>
#include <sstream>
#include <string>
#include "print_message.hh"
#include "instantiate_skeleton.hh"
#include "rename_files.hh"
#include "memory.hh"
#include "mapping.hh"
#include <algorithm>
#include <utility>
#include <map>
#include "session.hh"

namespace po = boost::program_options;

namespace {
skel::session
create_session(po::options_description const& desc, po::variables_map const& conf)
{
    skel::session work;
    if( conf.count("help") ) {
        std::ostringstream ss;
        ss << " Usage: skel [options] [--skeleton=]<skeleton>\n\n" << desc;
        work.add(mn::make_unique<skel::print_message>(ss.str()));
    }
    if( conf.count("skeleton") ) {
        std::map<std::string,std::string> subs;
        if( conf.count("substitute") ) {
            auto const cl = conf["substitute"].as<std::vector<skel::mapping>>();
            std::transform(cl.begin(), cl.end(),
                           std::inserter(subs, subs.end()),
                           [&](skel::mapping const& m) {
                               return std::make_pair(m.from, m.to);
                           });
        }
        auto const skeleton_name = conf["skeleton"].as<std::string>();
        work.add(mn::make_unique<skel::instantiate_skeleton>(skeleton_name, subs));
    }
    if( conf.count("rename") ) {
        auto const maps_from_cmdline = conf["rename"].as<std::vector<skel::mapping>>();
        std::map<std::string,std::string> renames;
        std::transform(maps_from_cmdline.begin(), maps_from_cmdline.end(),
                       std::inserter(renames, renames.end()),
                       [&](skel::mapping const& m) {
                           return std::make_pair(m.from, m.to);
                       });
        work.add(mn::make_unique<skel::rename_files>(renames));
    }
    return work;
}

skel::session parse_commandline(int argc, char const * argv[])
{
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "display this help message")
        ("substitute,s",
         po::value<std::vector<skel::mapping>>(),
         "define a substitution mapping")
        ("rename,r",
         po::value<std::vector<skel::mapping>>(),
         "define a rename mapping")
        ("skeleton,k", po::value<std::string>(), "pick skeleton to instantiate");
    po::positional_options_description positional;
    positional.add("skeleton", -1);
    po::variables_map conf;
    po::store(po::command_line_parser(argc, argv)
              .options(desc)
              .positional(positional)
              .run(), conf);
    po::notify(conf);
    return create_session(desc, conf);
}
}

namespace skel {
application::application(int argc, char const * argv[])
: work(parse_commandline(argc, argv))
{
}

void application::exec()
{
    work.exec();
}
}  // namespace skel
