#include "mapping.hh"
#include <vector>
#include <string>
#include <boost/any.hpp>
#include <boost/regex.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/errors.hpp>

namespace po = boost::program_options;

namespace skel {
mapping::mapping(std::string const& from, std::string const& to)
: from(from)
, to(to)
{
}

void validate(boost::any& v,
              std::vector<std::string> const& values,
              mapping*, int)
{
    static boost::regex const regex("([^:]*):(.*)");
    po::validators::check_first_occurrence(v);
    std::string const& str = po::validators::get_single_string(values);
    boost::smatch match;
    if( ! boost::regex_match(str, match, regex) )
        throw po::validation_error(po::validation_error::invalid_option_value);
    v = mapping(match[1], match[2]);
}
}  // namespace skel
