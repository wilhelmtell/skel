#ifndef SKELETON_HH_
#define SKELETON_HH_

#include <string>

namespace skel {
struct skeleton {
    explicit skeleton(std::string const& name);
    void instantiate() const;
private:
    std::string name;
};

bool skeleton_installed(std::string const& name);
}  // namespace skel

#endif  // SKELETON_HH_
