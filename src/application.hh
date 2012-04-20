#ifndef APPLICATION_HH_
#define APPLICATION_HH_

#include "session.hh"
#include "command.hh"

namespace skel {
struct application {
    application(int argc, char const * const argv[]);

    void exec();

private:
    session work;
};
}  // namespace skel

#endif  // APPLICATION_HH_
