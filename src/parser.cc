#include "parser.hh"
#include "scanner.hh"
#include <iosfwd>
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

void parse_macro(std::istream& in, std::ostream& out,
                 std::map<std::string,std::string> const& substitutions)
{
    skel::token t = skel::scan(in);
    auto const pos = substitutions.find(t.value);
    out << (pos == substitutions.end() ? t.value : pos->second);
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
            parse_macro_begin(in);
        } else if( t.type == token::MACRO_END ) {
            parse_macro_end(in);
        } else if( t.type == token::MACRO ) {
            parse_macro(in, out, substitutions);
        } else if( t.type == token::EOS ) {
            parse_eos(in);
        }
    }
}
}  // namespace skel
