#ifndef INSTANTIATE_PARTS_HH_
#define INSTANTIATE_PARTS_HH_

#include "instantiate_part.hh"
#include <stack>

namespace skel {
struct instantiate_parts {
    instantiate_parts();
    instantiate_parts(instantiate_parts const&) = delete;
    instantiate_parts& operator=(instantiate_parts const&) = delete;
    instantiate_parts(instantiate_parts&&) = default;
    ~instantiate_parts() noexcept;

    void commit();
    void add(instantiate_part p);

private:
    bool committed;
    std::stack<instantiate_part> parts;
};
}  // namespace skel

#endif  // INSTANTIATE_PARTS_HH_
