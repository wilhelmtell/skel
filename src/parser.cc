#include "parser.hh"
#include "scanner.hh"
#include <iostream>
#include <map>
#include <string>
#include "parser_error.hh"

namespace {
void parse_terminal(skel::scanner& s, std::ostream& out)
{
    skel::token t(s.scan());
    out << t.value;
}

void parse_esc(skel::scanner& s, std::ostream& out)
{
    skel::token t(s.scan());
    out << t.value;
}

void parse_macro_begin(skel::scanner& s)
{
    s.scan();
}

void parse_macro_end(skel::scanner& s)
{
    s.scan();
}

void parse_macro_name(skel::scanner& s, std::ostream& out,
                      std::map<std::string,std::string> const& substitutions)
{
    skel::token t(s.scan());
    auto const pos = substitutions.find(t.value);
    if( pos == substitutions.end() )
        out << '{' << t.value << '}';
    else
        out << pos->second;
}

void parse_macro(skel::scanner& s, std::ostream& out,
                 std::map<std::string,std::string> const& substitutions)
{
    parse_macro_begin(s);
    if( s.peek().type != skel::token::MACRO )
        throw skel::syntax_error("expected macro name here");
    parse_macro_name(s, out, substitutions);
    if( s.peek().type != skel::token::MACRO_END )
        throw skel::syntax_error("expected macro end here");
    parse_macro_end(s);
}

void parse_eos(skel::scanner& s)
{
    s.scan();
}
}  // namespace

namespace skel {
void parse(std::istream& in, std::ostream& out,
           std::map<std::string,std::string> const& substitutions)
{
    scanner s(in);
    for( token t(s.peek()); t.type != token::EOS; t = s.peek() ) {
        if( t.type == token::TERMINAL ) {
            parse_terminal(s, out);
        } else if( t.type == token::ESC ) {
            parse_esc(s, out);
        } else if( t.type == token::MACRO_BEGIN ) {
            parse_macro(s, out, substitutions);
        }
    }
    parse_eos(s);
}
}  // namespace skel
