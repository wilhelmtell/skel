#ifndef RENAMES_ATOM_TCC_
#define RENAMES_ATOM_TCC_

#include "renames_atom.tcc"
#include <utility>

namespace skel {
template<typename... Args>
void renames_atom::add(Args&&... args)
{
    renames.push_back(mv(std::forward<Args>(args)...));
}
}  // namespace skel

#endif  // RENAMES_ATOM_TCC_
