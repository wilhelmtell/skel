#include "utility.hh"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>
#include <vector>
#include "config.hh"

namespace fs = boost::filesystem3;

namespace skel {
void copy_r(fs::path const& from, fs::path const& to)
{
    auto const from_parent = from.parent_path();
    auto const parent_path_length = std::distance(from_parent.begin(),
                                                  from_parent.end());
    std::vector<fs::path> copied;
    std::for_each(fs::recursive_directory_iterator(from),
                  fs::recursive_directory_iterator(),
                  [&](fs::directory_entry const& ent) {
        auto const current = ent.path();
        TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
            << "copying " << current.string();
        auto const relative_pos = std::next(current.begin(),
                                            parent_path_length + 1);
        auto const current_to = std::accumulate(relative_pos, current.end(),
                                                to, std::divides<fs::path>());
        try {
            fs::copy(current, current_to);
        } catch( fs::filesystem_error const& e ) {
            TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
                << "failed copying " << current.string() << "; rolling back ...";
            boost::system::error_code e;
            std::for_each(copied.rbegin(), copied.rend(), [&e](fs::path const& p) {
                TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
                    << "removing " << p.string() << " ...";
                fs::remove(p, e);
            });
            throw;
        }
        copied.push_back(current_to);
    });
}
}  // namespace skel
