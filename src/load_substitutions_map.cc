#include "load_substitutions_map.hh"
#include <map>
#include <string>
#include <iostream>

struct bad_substitutions_map { };

namespace skel {
void load_substitutions_map(std::istream& in,
                            std::map<std::string,std::string>& subs)
{
    for( std::string name, value; in; ) {
        if( !(in >> name) ) throw bad_substitutions_map();
        std::getline(in, value);
        subs[name] = value;
    }
}
}  // namespace skel
