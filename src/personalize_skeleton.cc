#include "personalize_skeleton.hh"
#include <fstream>

namespace skel {
void personalize_skeleton(boost::filesystem3::path const& p)
{
    std::ifstream file(p.string());
}
}  // namespace skel
