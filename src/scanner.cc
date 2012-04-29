#include "scanner.hh"
#include <iostream>
#include <sstream>
#include <string>

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

scanner::scanner(std::istream& in)
: in(in)
{
}

token scanner::peek()
{
    if( tokens_queue.empty() )
        scan_force();
    return tokens_queue.front();
}

token scanner::scan()
{
    if( tokens_queue.empty() )
        scan_force();
    return scan_cache();
}

void scanner::scan_force()
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

skel::token scanner::scan_cache()
{
    auto const cached = tokens_queue.front();
    tokens_queue.pop();
    return cached;
}
}  // namespace skel
