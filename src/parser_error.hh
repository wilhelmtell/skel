#ifndef PARSER_ERROR_HH_
#define PARSER_ERROR_HH_

#include <stdexcept>
#include <string>

namespace skel {
struct syntax_error : public std::runtime_error {
    syntax_error(std::string const& m) : std::runtime_error(m) { }
};

}  // namespace skel

#endif  // PARSER_ERROR_HH_
