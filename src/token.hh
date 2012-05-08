#ifndef TOKEN_HH_
#define TOKEN_HH_

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

    token(token_t type);
    token(token_t type, std::string const& value);

    std::string value;
};
}  // namespace skel

#endif  // TOKEN_HH_
