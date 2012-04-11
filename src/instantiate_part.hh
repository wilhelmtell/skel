#ifndef INSTANTIATE_PART_HH_
#define INSTANTIATE_PART_HH_

#include <boost/filesystem.hpp>
#include <map>
#include <string>
#include "copy_part.hh"

namespace skel {
struct instantiate_part {
    instantiate_part(boost::filesystem3::path const& from,
                     boost::filesystem3::path const& to,
                     std::map<std::string,std::string> const& mappings);

    void commit();

private:
    copy_part cp;
};

}  // namespace skel

#endif  // INSTANTIATE_PART_HH_
