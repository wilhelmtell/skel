#include "print_message.hh"
#include <iostream>

namespace skel {
print_message::print_message(std::string const& msg)
: msg(msg)
{
}

void print_message::operator()() const
{
    std::cout << msg;
}
}  // namespace skel
