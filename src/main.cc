#include "scanner.hh"
#include <cassert>
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    skel::token token = skel::scan(std::cin);
    while( token.type != skel::token::EOS ) {
        if( token.type == skel::token::TERMINAL )
            std::cout << "TERMINAL " << (token.value == "\n" ? "nl" : token.value) << '\n';
        else if( token.type == skel::token::ESC )
            std::cout << "ESC " << token.value << '\n';
        else if( token.type == skel::token::MACRO_BEGIN )
            std::cout << "MACRO_BEGIN\n";
        else if( token.type == skel::token::MACRO_END )
            std::cout << "MACRO_END\n";
        else if( token.type == skel::token::MACRO )
            std::cout << "MACRO " << token.value << '\n';
        else if( token.type == skel::token::EOS )
            std::cout << "EOS\n";
        else 
            std::cout << "UNKNOWN " << token.value << '\n';
        token = skel::scan(std::cin);
    }
    assert(token.type == skel::token::EOS);
    std::cout << "EOS\n";
    return 0;
}
