#include "instantiate_part.hh"
#include <boost/filesystem.hpp>
#include <string>
#include <map>
#include "parser.hh"
#include <fstream>
#include <sstream>

namespace fs = boost::filesystem;

namespace skel {
instantiate_part::instantiate_part(fs::path const& from, fs::path const& to,
                                   std::map<std::string,std::string> const& mappings)
: cp(from, to)
{
    if( fs::is_regular_file(from) ) {
        std::ostringstream buf;
        std::ifstream in(from.string());
        skel::parse(in, buf, mappings);
        std::ofstream(to.string()) << buf.str();
    }
}

void instantiate_part::commit()
{
    cp.commit();
}
}  // namespace skel
