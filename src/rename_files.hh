#ifndef RENAME_FILES_HH_
#define RENAME_FILES_HH_

#include "command.hh"
#include <map>
#include <string>

namespace skel {
struct rename_files : public command {
    rename_files(std::map<std::string,std::string> const& mappings);

    void operator()() const;

private:
    std::map<std::string,std::string> mappings;
};
}  // namespace skel

#endif  // RENAME_FILES_HH_
