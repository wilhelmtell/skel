#include "parser.hh"
#include "scanner.hh"
#include <iostream>
#include <map>
#include <string>

namespace {
void parse_terminal(std::istream& in, std::ostream& out)
{
    skel::token t = skel::scan(in);
    out << t.value;
}

void parse_esc(std::istream& in, std::ostream& out)
{
    skel::token t = skel::scan(in);
    out << t.value;
}

void parse_macro_begin(std::istream& in)
{
    skel::scan(in);
}

void parse_macro_end(std::istream& in)
{
    skel::scan(in);
}

void parse_macro_name(std::istream& in, std::ostream& out,
                      std::map<std::string,std::string> const& substitutions)
{
    skel::token t = skel::scan(in);
    auto const pos = substitutions.find(t.value);
    if( pos == substitutions.end() )
        out << '{' << t.value << '}';
    else
        out << pos->second;
}

void parse_macro(std::istream& in, std::ostream& out,
                 std::map<std::string,std::string> const& substitutions)
{
    parse_macro_begin(in);
    if( skel::peek(in).type != skel::token::MACRO )
        throw skel::syntax_error("expected macro name here");
    parse_macro_name(in, out, substitutions);
    if( skel::peek(in).type != skel::token::MACRO_END )
        throw skel::syntax_error("expected macro end here");
    parse_macro_end(in);
}

void parse_eos(std::istream& in)
{
    skel::token t = skel::scan(in);
}
}  // namespace

namespace skel {
void parse(std::istream& in, std::ostream& out,
           std::map<std::string,std::string> const& substitutions)
{
    for( token t = peek(in); t.type != token::EOS; t = peek(in) ) {
        if( t.type == token::TERMINAL ) {
            parse_terminal(in, out);
        } else if( t.type == token::ESC ) {
            parse_esc(in, out);
        } else if( t.type == token::MACRO_BEGIN ) {
            parse_macro(in, out, substitutions);
        } else if( t.type == token::EOS ) {
            parse_eos(in);
        }
    }
}
}  // namespace skel
