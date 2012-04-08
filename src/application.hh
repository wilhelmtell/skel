#ifndef APPLICATION_HH_
#define APPLICATION_HH_

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/function.hpp>

namespace skel {
struct application {
    application(int argc, char *argv[]);

    bool exec() const;

private:
    boost::program_options::options_description desc;
    boost::program_options::variables_map conf;
    boost::function<bool (boost::program_options::options_description const&,
                          boost::program_options::variables_map const&)>
                    exec_func;
};
}  // namespace skel

#endif  // APPLICATION_HH_
