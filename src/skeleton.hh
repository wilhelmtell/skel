#ifndef SKELETON_HH_
#define SKELETON_HH_

#include <string>
#include <map>

namespace skel {
struct skeleton {
    skeleton(std::string const& name,
             std::map<std::string,std::string> const& subs);
    void instantiate() const;
private:
    std::string name;
    std::map<std::string,std::string> const& subs;
};

bool skeleton_installed(std::string const& name);

// first and last are iterators over a sequence of skeleton names (strings)
template<typename In>
bool instantiate_skeletons(In first, In last);
}  // namespace skel

#include "skeleton.tcc"

#endif  // SKELETON_HH_
