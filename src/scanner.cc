#include "scanner.hh"
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

namespace {
std::queue<skel::token> tokens_queue;

void scan_force(std::istream& in)
{
    char c;
    if( ! in.get(c) ) {
        tokens_queue.push(skel::token(skel::token::EOS));
    } else if( c == '\\' ) {
        char c1;
        if( ! in.get(c1) ) {
            tokens_queue.push(skel::token(skel::token::ESC, "\\"));
            tokens_queue.push(skel::token::EOS);
        } else {
            std::ostringstream ss;
            ss << c1;
            tokens_queue.push(skel::token(skel::token::ESC, ss.str()));
        }
    } else if( c == '{' ) {
        tokens_queue.push(skel::token(skel::token::MACRO_BEGIN));
        std::string macro;
        while( in.get(c) && c != '\n' && c != '}' )
            macro += c;
        tokens_queue.push(skel::token(skel::token::MACRO, macro));
        if( ! in )
            tokens_queue.push(skel::token(skel::token::EOS));
        else if( c == '\n' )
            tokens_queue.push(skel::token(skel::token::TERMINAL, "\n"));
        else
            tokens_queue.push(skel::token(skel::token::MACRO_END));
    } else {
        std::ostringstream ss;
        ss << c;
        tokens_queue.push(skel::token(skel::token::TERMINAL, ss.str()));
    }
}

skel::token scan_cache()
{
    auto const cached = tokens_queue.front();
    tokens_queue.pop();
    return cached;
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

token peek(std::istream& in)
{
    if( tokens_queue.empty() )
        scan_force(in);
    return tokens_queue.front();
}

token scan(std::istream& in)
{
    if( tokens_queue.empty() )
        scan_force(in);
    return scan_cache();
}
}  // namespace skel
