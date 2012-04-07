#ifndef APPLICATION_HH_
#define APPLICATION_HH_

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>

namespace skel {
struct application {
    application(int argc, char *argv[]);

    bool exec() const;

private:
    boost::program_options::options_description desc;
    boost::program_options::variables_map conf;
    bool (*exec_func)(boost::program_options::options_description const&,
                      boost::program_options::variables_map const&);
};
}  // namespace skel

#endif  // APPLICATION_HH_
