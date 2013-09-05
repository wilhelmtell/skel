#include "renames_atom.hh"
#include "mv.hh"

namespace skel {
renames_atom::renames_atom()
{
}

void renames_atom::commit()
{
    for( auto& r : renames )
        r.commit();
}
}  // namespace skel
