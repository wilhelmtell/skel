#include "application.hh"
#include <iostream>
#include "parser.hh"
#include <boost/program_options/errors.hpp>

namespace {
std::string unknown_error_message()
{
    return
        "will you be so kind and send me an email with step-by-step\n"
        "instructions on how to reproduce this error? i'd love to fix it, but\n"
        "i need to know about it first. my email address is\n"
        "matan.nassau@gmail.com.\n";
}

void unknown_error(std::runtime_error const& e)
{
    std::cerr
        << "unknown runtime error: " << e.what() << "\n\n"
        << unknown_error_message();
}

void unknown_error(std::logic_error const& e)
{
    std::cerr
        << "unknown logic error: " << e.what() << "\n\n"
        << unknown_error_message();
}

void unknown_error()
{
    std::cerr << "unknown error\n\n" << unknown_error_message();
}
}

int main(int argc, char* argv[])
{
    try {
        skel::application app(argc, argv);
        return ! app.exec();
    } catch( boost::program_options::required_option const& e ) {
        std::cerr << "please specify a skeleton to instantiate.\n";
        return 1;
    } catch( skel::syntax_error const& e ) {
        std::cerr << "skeleton syntax error.\n";
        return 1;
    // i can't see how any of the following exceptions will propagate, but i
    // don't trust myself here.
    } catch( std::runtime_error const& e ) {
        unknown_error(e);
        return 1;
    } catch( std::logic_error const& e ) {
        unknown_error(e);
        return 1;
    } catch( ... ) {
        unknown_error();
        return 1;
    }
}
