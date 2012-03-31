#include <iostream>
#include "parser.hh"
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

std::map<std::string,std::string> parse_substitutions(int count, char * pairs[])
{
    std::map<std::string,std::string> substitutions;
    for( int i = 0; i != count; ++i ) {
        std::string pair = pairs[i];
        auto const delim_pos = std::find(pair.begin(), pair.end(), ':');
        if( delim_pos == pair.end() )
            return substitutions;
        std::string from(pair.begin(), delim_pos);
        std::string to(std::next(delim_pos), pair.end());
        substitutions.insert(std::make_pair(from, to));
    }
    return substitutions;
}

int main(int argc, char* argv[])
{
    try {
        std::map<std::string,std::string> substitutions{
            parse_substitutions(argc - 1, &argv[1])
        };
        skel::parse(std::cin, std::cout, substitutions);
    } catch( skel::syntax_error const& e) {
        std::cerr << "syntax error: " << e.what() << '\n';
    }
    return 0;
}
