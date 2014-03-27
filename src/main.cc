#include "application.hh"
#include <iostream>
#include "parser_error.hh"
#include <boost/program_options/errors.hpp>
#include "invalid_user_interface_input.hh"
#include "skeleton_instantiation_error.hh"

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
        "if you send me an email at matan.nassau@gmail.com so i learn about\n"
        "this then that would be splendid!\n";
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
    } catch( skel::skeleton_instantiation_error const& e ) {
        std::cerr << "skeleton instantiation error: " << e.what() << '\n';
        return 0x7ffd;
    } catch( boost::program_options::error const& e ) {
        std::cerr << "program options error: " << e.what() << '\n';
        return 0x7ffc;
    } catch( std::exception const& e ) {
        unknown_error(e);
        DEBUG_THROW;
        return 1;
    }
    return 0;
}
