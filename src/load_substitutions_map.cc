#include "load_substitutions_map.hh"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace skel {
void load_substitutions_map(std::istream& in,
                            std::map<std::string,std::string>& subs)
{
    for( std::string name, value; in >> name && std::getline(in, value); ) {
        auto const non_space_pos = std::find_if(value.begin(), value.end(), 
                                                [](char c) {
                                                    return ! std::isspace(c);
                                                });
        value.erase(value.begin(), non_space_pos);
        subs[name] = value;
    }
}
}  // namespace skel
