#ifndef SCANNER_HH_
#define SCANNER_HH_

#include <iosfwd>
#include <string>
#include <queue>
#include "token.hh"

namespace skel {
struct scanner {
    scanner(std::istream& in);

    token peek();
    token scan();

private:
    void scan_force();
    token scan_cache();

private:
    std::istream& in;
    std::queue<skel::token> tokens_queue;
};
}  // namespace skel

#endif  // SCANNER_HH_
