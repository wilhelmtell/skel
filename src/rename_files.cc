#include "rename_files.hh"
#include <boost/filesystem.hpp>
#include <algorithm>
#include <map>
#include <string>

namespace fs = boost::filesystem3;

namespace skel {
rename_files::rename_files(std::map<std::string,std::string> const& mappings)
: mappings(mappings)
{
}

void rename_files::execute()
{
    std::for_each(fs::recursive_directory_iterator(fs::current_path()),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        auto const ent_path = ent.path();
        auto const rename_mapping_pos = mappings.find(ent_path.filename().string());
        if( rename_mapping_pos != mappings.end() ) {
            auto const to = ent_path.parent_path() / rename_mapping_pos->second;
            renames.add(ent_path, to);
        }
    });
}

void rename_files::commit()
{
    renames.commit();
}
}  // namespace skel
