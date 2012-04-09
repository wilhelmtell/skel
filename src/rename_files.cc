#include "rename_files.hh"
#include "rename_files_error.hh"
#include <boost/filesystem.hpp>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <utility>

namespace fs = boost::filesystem3;

namespace {
struct mv {
    mv(fs::path const& from, fs::path const& to);
    ~mv();
    mv(mv&& rhs);
    mv(mv const&) = delete;
    mv& operator=(mv const&) = delete;

    void commit();

private:
    bool owning;
    std::string from;
    std::string to;
};

mv::mv(fs::path const& from, fs::path const& to)
: owning(true)
, from(from.string())
, to(to.string())
{
    if( fs::exists(to) )
        throw skel::rename_files_error(this->to + " already exists");
    fs::rename(from, to);
}

mv::~mv()
{
    if( owning )
        fs::rename(to, from);
}

mv::mv(mv&& rhs)
: owning(false)
, from()
, to()
{
    std::swap(rhs.owning, owning);
    std::swap(rhs.from, from);
    std::swap(rhs.to, to);
}

void mv::commit()
{
    owning = false;
}


struct renames_atom {
    renames_atom();
    renames_atom(renames_atom const&) = delete;
    renames_atom& operator=(renames_atom const&) = delete;

    void commit();

    template<typename... Args>
    void add(Args&&... args);

private:
    bool owning;
    std::vector<mv> renames;
};

renames_atom::renames_atom()
: owning(true)
{
}

void renames_atom::commit()
{
    for( auto& r : renames )
        r.commit();
}

template<typename... Args>
void renames_atom::add(Args&&... args)
{
    renames.push_back(mv(std::forward<Args>(args)...));
}
}

namespace skel {
rename_files::rename_files(std::map<std::string,std::string> const& mappings)
: mappings(mappings)
{
}

void rename_files::operator()() const
{
    renames_atom renames;
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
    renames.commit();
}
}  // namespace skel
