#include "application.hh"
#include <iostream>
#include "parser_error.hh"
#include <boost/program_options/errors.hpp>

#ifndef NDEBUG
#include <execinfo.h>
#endif

namespace {
std::string unknown_error_message()
{
    return
        "will you be so kind and send me an email to matan.nassau@gmail.com\n"
        "with step-by-step instructions on how to reproduce this error? i'd\n"
        "love to fix it, but i need to know about it first.\n";
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
        app.exec();
    } catch( boost::program_options::required_option const& e ) {
        std::cerr << "please specify a skeleton to instantiate.\n";
        return 1;
    } catch( skel::syntax_error const& e ) {
        std::cerr << "skeleton syntax error: " << e.what() << '\n';
        return 2;
    // i can't see how any of the following exceptions will propagate, but i
    // don't trust myself here.
    } catch( std::runtime_error const& e ) {
        unknown_error(e);
        return 3;
    } catch( std::logic_error const& e ) {
        unknown_error(e);
        return 4;
    } catch( ... ) {
        unknown_error();
#ifndef NDEBUG
        void * stacktrace[128];
        std::size_t size = backtrace(stacktrace, 128);
        backtrace_symbols_fd(stacktrace, size, 2);
        throw;
#endif
        return 5;
    }
    return 0;
}
