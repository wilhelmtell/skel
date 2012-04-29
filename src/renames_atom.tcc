#ifndef RENAMES_ATOM_TCC_
#define RENAMES_ATOM_TCC_

#include "renames_atom.tcc"
#include <utility>
#include "skeleton_instantiation_error.hh"

namespace skel { struct rename_files_error; }

namespace skel {
template<typename... Args>
void renames_atom::add(Args&&... args)
{
    try {
        renames.push_back(mv(std::forward<Args>(args)...));
    } catch( skel::rename_files_error const& e ) {
        throw skel::skeleton_instantiation_error();
    }
}
}  // namespace skel

#endif  // RENAMES_ATOM_TCC_
