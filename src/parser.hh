#ifndef PARSER_HH_
#define PARSER_HH_

#include <iosfwd>
#include <map>
#include <string>

namespace skel {
void parse(std::istream& in, std::ostream& out,
           std::map<std::string,std::string> const& substitutions);
}  // namespace skel

#endif  // PARSER_HH_
