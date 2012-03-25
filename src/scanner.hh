#ifndef SCANNER_HH_
#define SCANNER_HH_

#include <iosfwd>
#include <string>

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
    std::string value;

    token(token_t type);
    token(token_t type, std::string const& value);
};

token peek(std::istream& in);
token scan(std::istream& in);
}  // namespace skel

#endif  // SCANNER_HH_
