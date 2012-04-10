#ifndef INSTANTIATE_SKELETON_HH_
#define INSTANTIATE_SKELETON_HH_

#include "command.hh"
#include <string>
#include <map>

namespace skel {
struct instantiate_skeleton : public command {
    instantiate_skeleton(std::string const& name,
                         std::map<std::string,std::string> const& mappings);

    void execute() const;

private:
    std::string const name;
    std::map<std::string,std::string> mappings;
};
}  // namespace skel

#endif  // INSTANTIATE_SKELETON_HH_
