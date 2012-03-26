#include <iostream>
#include "parser.hh"
#include <string>
#include <map>

int main(int /*argc*/, char* /*argv*/[])
{
    std::map<std::string,std::string> substitutions{
        {"APPNAME", "skel"},
        {"VERSION", "0.1"}
    };
    try {
        skel::parse(std::cin, std::cout, substitutions);
    } catch( skel::syntax_error const& e) {
        std::cerr << "syntax error: " << e.what() << '\n';
    }
    return 0;
}
