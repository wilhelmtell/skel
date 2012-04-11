#include "renames_atom.hh"
#include "mv.hh"

namespace skel {
renames_atom::renames_atom()
: owning(true)
{
}

void renames_atom::commit()
{
    for( auto& r : renames )
        r.commit();
}
}  // namespace skel
