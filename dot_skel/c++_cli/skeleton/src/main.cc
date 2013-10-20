#include <iostream>
#include <exception>
#include "commandline.hh"

int main(int argc, char const * argv[])
\{
    try \{
        auto const desc({APPNAME}::options_description());
        auto const vm({APPNAME}::variables_map(argc, argv, desc));
        if( vm.count("help") )
            {APPNAME}::print_help(argv[0], desc);
        else
            {APPNAME}::exec(vm);
        return 0;
    \} catch( std::exception const& e ) \{
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    \}
\}
