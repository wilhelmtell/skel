#ifndef MAPPING_HH_
#define MAPPING_HH_

#include <string>
#include <iosfwd>

namespace skel {
struct mapping {
    std::string from;
    std::string to;
};

std::istream& operator>>(std::istream& in, mapping& m);
std::ostream& operator<<(std::ostream& out, mapping const& m);
}  // namespace skel

#endif  // MAPPING_HH_
