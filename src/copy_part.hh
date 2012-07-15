#ifndef COPY_PART_HH_
#define COPY_PART_HH_

#include <string>
#include <boost/filesystem.hpp>

namespace skel {
struct copy_part {
    copy_part(boost::filesystem::path const& from,
              boost::filesystem::path const& to);
    copy_part(copy_part const&) = delete;
    copy_part& operator=(copy_part const&) = delete;
    copy_part(copy_part&& rhs);
    ~copy_part() noexcept;

    void commit();

private:
    bool owning;
    std::string to;  // HACK: should be an fs::path, but fs::path isn't moveable
};
}  // namespace skel

#endif  // COPY_PART_HH_
