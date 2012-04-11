#include "session.hh"
#include <vector>
#include "command.hh"

namespace skel {
void session::add(std::unique_ptr<command> c)
{
    work.push_back(std::move(c));
}

void session::exec()
{
    for( auto const& c : work )
        c->execute();
    for( auto const& c : work )
        c->commit();
}
}  // namespace skel
