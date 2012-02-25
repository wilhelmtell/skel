#ifndef LOAD_SUBSTITUTIONS_MAP_HH_
#define LOAD_SUBSTITUTIONS_MAP_HH_

#include <map>
#include <iosfwd>
#include <string>

namespace skel {
void load_substitutions_map(std::istream& in,
                            std::map<std::string,std::string>& subs);
}  // namespace skel

#endif  // LOAD_SUBSTITUTIONS_MAP_HH_
