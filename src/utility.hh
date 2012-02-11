#ifndef UTILITY_HH_
#define UTILITY_HH_

#include <boost/filesystem/path.hpp>

namespace skel {
void copy_r(boost::filesystem3::path const& from, boost::filesystem3::path const& to);
}  // namespace skel

#endif  // UTILITY_HH_
