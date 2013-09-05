#ifndef RENAMES_ATOM_HH_
#define RENAMES_ATOM_HH_

#include <vector>
#include "mv.hh"

namespace skel {
struct renames_atom {
    renames_atom();
    renames_atom(renames_atom const&) = delete;
    renames_atom& operator=(renames_atom const&) = delete;

    void commit();

    template<typename... Args>
    void add(Args&&... args);

private:
    std::vector<mv> renames;
};
}  // namespace skel

#include "renames_atom.tcc"

#endif  // RENAMES_ATOM_HH_
