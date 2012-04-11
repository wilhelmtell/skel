#ifndef RENAME_FILES_HH_
#define RENAME_FILES_HH_

#include "command.hh"
#include <map>
#include <string>
#include "renames_atom.hh"

namespace skel {
struct rename_files : public command {
    rename_files(std::map<std::string,std::string> const& mappings);
    rename_files(rename_files const&) = delete;
    rename_files& operator=(rename_files const&) = delete;

    void execute();
    void commit();

private:
    std::map<std::string,std::string> mappings;
    renames_atom renames;
};
}  // namespace skel

#endif  // RENAME_FILES_HH_
