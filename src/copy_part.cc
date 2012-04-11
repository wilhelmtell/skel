#include "copy_part.hh"
#include <boost/filesystem.hpp>
#include <algorithm>

namespace fs = boost::filesystem3;

namespace skel {
copy_part::copy_part(fs::path const& from, fs::path const& to)
: owning(true)
, to(to.string())
{
    fs::copy(from, to);
}

copy_part::~copy_part() noexcept
{
    if( owning ) {
        boost::system::error_code e;
        fs::remove(to, e);
    }
}

copy_part::copy_part(copy_part&& rhs)
: owning(false)
, to()
{
    std::swap(rhs.owning, owning);
    std::swap(rhs.to, to);
}

void copy_part::commit()
{
    owning = false;
}
}  // namespace skel
