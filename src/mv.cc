#include "mv.hh"
#include <boost/filesystem.hpp>
#include <string>
#include "skeleton_instantiation_error.hh"
#include <algorithm>

namespace fs = boost::filesystem3;

namespace skel {
mv::mv(fs::path const& from, fs::path const& to)
: owning(true)
, from(from.string())
, to(to.string())
{
    if( fs::exists(to) )
        throw skel::skeleton_instantiation_error(this->to + " already exists");
    fs::rename(from, to);
}

mv::~mv() noexcept
{
    boost::system::error_code e;
    if( owning )
        fs::rename(to, from, e);
}

mv::mv(mv&& rhs)
: owning(false)
, from()
, to()
{
    std::swap(rhs.owning, owning);
    std::swap(rhs.from, from);
    std::swap(rhs.to, to);
}

void mv::commit()
{
    owning = false;
}
}  // namespace skel
