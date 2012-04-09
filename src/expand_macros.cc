#include "expand_macros.hh"
#include <map>
#include <string>
#include <sstream>
#include "parser.hh"
#include <iostream>

namespace skel {
expand_macros::expand_macros(std::map<std::string,std::string> const& mappings)
: mappings(mappings)
{
}

void expand_macros::operator()() const
{
    std::ostringstream out;
    skel::parse(std::cin, out, mappings);
    std::cout << out.str();
}

}  // namespace skel
