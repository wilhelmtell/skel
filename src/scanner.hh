#ifndef SCANNER_HH_
#define SCANNER_HH_

#include <iosfwd>
#include <string>
#include <stdexcept>

namespace skel {
struct syntax_error : public std::runtime_error {
    syntax_error(std::string const& m) : std::runtime_error(m) { }
};

struct token {
    enum token_t {
        TERMINAL = 1,
        ESC,
        MACRO_BEGIN,
        MACRO_END,
        EOS
    } type;
    std::string value;

    token(token_t type);
    token(token_t type, std::string const& value);
};

token scan(std::istream& in);
}  // namespace skel

#endif  // SCANNER_HH_
