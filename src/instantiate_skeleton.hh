#ifndef INSTANTIATE_SKELETON_HH_
#define INSTANTIATE_SKELETON_HH_

#include "command.hh"
#include <string>

namespace skel {
struct instantiate_skeleton : public command {
    instantiate_skeleton(std::string const& name);

    void operator()() const;

private:
    std::string const name;
};
}  // namespace skel

#endif  // INSTANTIATE_SKELETON_HH_
