#include "application.hh"
#include <iostream>
#include "parser_error.hh"
#include "rename_files_error.hh"
#include <boost/program_options/errors.hpp>
#include "invalid_user_interface_input.hh"

#ifndef NDEBUG
#  include <execinfo.h>
#  define DEBUG_THROW throw
#else
#  define DEBUG_THROW
#endif

namespace {
std::string unknown_error_message()
{
#ifndef NDEBUG
    void * data[128];
    std::size_t size = backtrace(data, 128);
    backtrace_symbols_fd(data, size, 2);
#endif
    return
        "will you be so kind and send me an email to matan.nassau@gmail.com\n"
        "with step-by-step instructions on how to reproduce this error? i'd\n"
        "love to fix it, but i need to know about it first.\n";
}

void unknown_error(std::exception const& e)
{
    std::cerr
        << "unknown runtime error: " << e.what() << "\n\n"
        << unknown_error_message();
}
}  // local namespace

int main(int argc, char const * const argv[])
{
    try {
        skel::application app(argc, argv);
        app.exec();
    } catch( skel::invalid_user_interface_input const& e ) {
        std::cerr << "invalid user interface input.\n";
        return 0x7fff;
    } catch( skel::syntax_error const& e ) {
        std::cerr << "skeleton syntax error: " << e.what() << '\n';
        return 0x7ffe;
    } catch( skel::rename_files_error const& e ) {
        std::cerr << "rename error: " << e.what() << '\n';
        return 0x7ffd;
    } catch( std::exception const& e ) {
        unknown_error(e);
        DEBUG_THROW;
        return 1;
    }
    return 0;
}
