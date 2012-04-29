#ifndef SCANNER_HH_
#define SCANNER_HH_

#include <iosfwd>
#include <string>
#include <queue>

namespace skel {
struct token {
    enum token_t {
        TERMINAL = 1,
        ESC,
        MACRO_BEGIN,
        MACRO_END,
        MACRO,
        EOS
    } type;

    token(token_t type);
    token(token_t type, std::string const& value);

    std::string value;
};

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
