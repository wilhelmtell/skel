#ifndef APPLICATION_HH_
#define APPLICATION_HH_

#include <vector>
#include "command.hh"
#include <memory>

namespace skel {
struct application {
    application(int argc, char *argv[]);

    void exec() const;

private:
    std::vector<std::unique_ptr<command>> commands;
};
}  // namespace skel

#endif  // APPLICATION_HH_
