#ifndef MV_HH_
#define MV_HH_

#include <boost/filesystem.hpp>
#include <string>

namespace skel {
struct mv {
    mv(boost::filesystem::path const& from, boost::filesystem::path const& to);
    ~mv() noexcept;
    mv(mv&& rhs);
    mv(mv const&) = delete;
    mv& operator=(mv const&) = delete;

    void commit();

private:
    bool owning;
    std::string from;
    std::string to;
};
}  // namespace skel

#endif  // MV_HH_
