#include "parser.hh"
#include "scanner.hh"
#include <iosfwd>

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

void parse_macro(std::istream& in, std::ostream& /*out*/)
{
    skel::token t = skel::scan(in);
}

void parse_eos(std::istream& in)
{
    skel::token t = skel::scan(in);
}
}  // namespace

namespace skel {
void parse(std::istream& in, std::ostream& out)
{
    token t = peek(in);
    if( t.type == token::TERMINAL ) {
        parse_terminal(in, out);
    } else if( t.type == token::ESC ) {
        parse_esc(in, out);
    } else if( t.type == token::MACRO_BEGIN ) {
        parse_macro_begin(in);
    } else if( t.type == token::MACRO_END ) {
        parse_macro_end(in);
    } else if( t.type == token::MACRO ) {
        parse_macro(in, out);
    } else if( t.type == token::EOS ) {
        parse_eos(in);
    }
}
}  // namespace skel
