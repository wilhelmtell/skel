#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>

char const MACRO_BEGIN = '{';
char const MACRO_END = '}';
char const ESCAPE = '\\';

struct expand_macros {
    expand_macros(std::ostream& out);

    void operator()(char c);

private:
    std::ostream& out;
    bool escaped;
    bool reading_macro;
    std::string macro;
    std::map<std::string,std::string> substitutions;
};

expand_macros::expand_macros(std::ostream& out)
: out(out)
, escaped(false)
, reading_macro(false)
, macro()
, substitutions{{"APPNAME", "skel"}, {"VERSION", "0.1"}}
{ }

void expand_macros::operator()(char c)
{
    if( c == MACRO_BEGIN && ! escaped ) {
        reading_macro = true;
    } else if( c == MACRO_END && ! escaped ) {
        reading_macro = false;
        out << substitutions[macro];
        auto pos = substitutions.find(macro);
        if( pos == substitutions.end() )
            out << MACRO_BEGIN << macro << MACRO_END;
        else
            out << pos->second;
        macro.clear();
    } else if( reading_macro && ! escaped ) {
        macro += c;
    } else if( ! escaped ) {
        out << c;
    }
    escaped = c == ESCAPE && ! escaped;
}

int main(int argc, char* argv[])
{
    if( argc != 3 )
        return 1;
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    std::for_each(std::istreambuf_iterator<char>(in),
                  std::istreambuf_iterator<char>(),
                  expand_macros(out));
    return 0;
}
