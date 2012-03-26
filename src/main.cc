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
    skel::parse(std::cin, std::cout, substitutions);
    return 0;
}
