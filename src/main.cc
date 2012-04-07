#include "application.hh"
#include <iostream>
#include "parser.hh"
#include "mapping.hh"
#include <boost/program_options/errors.hpp>

int main(int argc, char* argv[])
{
    try {
        skel::application app(argc, argv);
    } catch( boost::program_options::required_option const& e ) {
        std::cerr << "please specify a skeleton to instantiate.\n";
        return 1;
    } catch( skel::syntax_error const& e ) {
        std::cerr << "skeleton syntax error.\n";
        return 1;
    // i can't see how any of the following exceptions will propagate, but i
    // don't trust myself here.
    } catch( std::runtime_error const& e ) {
        std::cerr << "runtime error: " << e.what() << '\n';
        return 1;
    } catch( std::logic_error const& e ) {
        std::cerr << "logic error: " << e.what() << '\n';
        return 1;
    } catch( ... ) {
        std::cerr << "unknown error. will you be so kind and send me an email "
            "with step-by-step instructions on how to reproduce this error? "
            "i'd love to fix it, but i need to know about it first. my email "
            "address is matan.nassau@gmail.com.\n";
        return 1;
    }
}
