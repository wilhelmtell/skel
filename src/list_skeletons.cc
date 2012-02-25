#include "list_skeletons.hh"
#include <iostream>
#include <iterator>
#include <string>
#include <boost/filesystem/operations.hpp>
#include "config.hh"

namespace fs = boost::filesystem3;

namespace {
template<typename In, typename Out, typename Op, typename Pred>
Out transform_if(In first, In last, Out out, Op op, Pred pred)
{
    while( first != last ) {
        if( pred(*first) ) *out++ = op(*first);
        ++first;
    }
    return out;
}
}  // namespace

namespace skel {
void list_skeletons()
{
    std::ostream& out = std::cout;
    transform_if(fs::directory_iterator(fs::path(USER_HOME) / skel::RC_DIR),
                 fs::directory_iterator(),
                 std::ostream_iterator<std::string>(out, "\n"),
                 [](fs::directory_entry const& ent) {
                     return ent.path().filename().string();
                 },
                 [](fs::directory_entry const& ent) {
                     return fs::is_directory(ent.path());
                 });
}

}  // namespace skel
