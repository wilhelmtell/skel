#ifndef EXPAND_MACROS_HH_
#define EXPAND_MACROS_HH_

#include "command.hh"
#include <string>
#include <map>

namespace skel {
struct expand_macros : public command {
    expand_macros(std::map<std::string,std::string> const& mappings);
    void operator()() const;

private:
    std::map<std::string,std::string> const mappings;
};
}  // namespace skel

#endif  // EXPAND_MACROS_HH_
