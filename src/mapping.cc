#include "mapping.hh"
#include <iostream>

namespace skel {
std::istream& operator>>(std::istream& in, mapping& m)
{
    for( char c; in.get(c) && c != ':'; m.from += c );
    for( char c; in.get(c); m.to += c );
    return in;
}

std::ostream& operator>>(std::ostream& out, mapping const& m)
{
    return out << m.from << ':' << m.to;
}
}  // namespace skel
