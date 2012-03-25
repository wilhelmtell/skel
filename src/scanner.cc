#include "scanner.hh"
#include <iostream>
#include <queue>
#include <sstream>

namespace {
std::queue<skel::token> tokens_queue;

skel::token scan_cache()
{
    auto const cached = tokens_queue.front();
    tokens_queue.pop();
    return cached;
}

skel::token scan_force(std::istream& in)
{
    char c;
    if( ! in.get(c) ) {
        return skel::token(skel::token::EOS);
    } else if( c == '\\' ) {
        char c1;
        if( ! in.get(c1) )
            throw skel::syntax_error("unexpected eos");
        if( c1 != '\\' && c1 != '{' && c1 != '}' )
            throw skel::syntax_error("invalid escape");
        std::ostringstream ss;
        ss << c1;
        return skel::token(skel::token::ESC, ss.str());
    } else if( c == '{' ) {
        return skel::token(skel::token::MACRO_BEGIN);
    } else if( c == '}' ) {
        return skel::token(skel::token::MACRO_END);
    } else {
        std::ostringstream ss;
        ss << c;
        return skel::token(skel::token::TERMINAL, ss.str());
    }
}

skel::token peek(std::istream& in)
{
    if( tokens_queue.empty() )
        tokens_queue.push(scan_force(in));
    return tokens_queue.front();
}
}  // namespace

namespace skel {
token::token(token_t type)
: type(type)
{
}

token::token(token_t type, std::string const& value)
: type(type)
, value(value)
{
}

token scan(std::istream& in)
{
    if( tokens_queue.empty() )
        return scan_force(in);
    else
        return scan_cache();
}
}  // namespace skel
