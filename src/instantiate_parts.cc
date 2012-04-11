#include "instantiate_parts.hh"
#include "instantiate_part.hh"
#include <utility>

namespace skel {
instantiate_parts::instantiate_parts()
: committed(false)
{
}

instantiate_parts::~instantiate_parts() noexcept
{
    if( ! committed ) {
        while( ! parts.empty() )
            parts.pop();
    }
}

void instantiate_parts::commit()
{
    committed = true;
    while( ! parts.empty() ) {
        parts.top().commit();
        parts.pop();
    }
}

void instantiate_parts::add(instantiate_part p)
{
    parts.push(std::move(p));
}
}  // namespace skel
