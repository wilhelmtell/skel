#ifndef PRINT_MESSAGE_HH_
#define PRINT_MESSAGE_HH_

#include "command.hh"
#include <string>

namespace skel {
struct print_message : public command {
    print_message(std::string const& msg);

    void execute();
    void commit();

private:
    std::string const msg;
};
}  // namespace skel

#endif  // PRINT_MESSAGE_HH_
