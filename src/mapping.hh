#ifndef MAPPING_HH_
#define MAPPING_HH_

#include <string>
#include <iosfwd>
#include <vector>

namespace boost { struct any; }

namespace skel {
struct mapping {
    mapping(std::string const& from, std::string const& to);
    std::string from;
    std::string to;
};

void validate(boost::any& v,
              std::vector<std::string> const& values,
              mapping*, int);
}  // namespace skel

#endif  // MAPPING_HH_
