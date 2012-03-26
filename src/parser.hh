#ifndef PARSER_HH_
#define PARSER_HH_

#include <iosfwd>
#include <map>
#include <string>
#include <stdexcept>

namespace skel {
struct syntax_error : public std::runtime_error {
    syntax_error(std::string const& m) : std::runtime_error(m) { }
};

void parse(std::istream& in, std::ostream& out,
           std::map<std::string,std::string> const& substitutions);
}  // namespace skel

#endif  // PARSER_HH_
