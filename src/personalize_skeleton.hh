#ifndef PERSONALIZE_SKELETON_HH_
#define PERSONALIZE_SKELETON_HH_

#include <boost/filesystem/path.hpp>

namespace skel {
void personalize_skeleton(boost::filesystem3::path const& in_path,
                          boost::filesystem3::path const& out_path);
}  // namespace skel

#endif  // PERSONALIZE_SKELETON_HH_
