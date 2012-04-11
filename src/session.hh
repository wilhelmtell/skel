#ifndef SESSION_HH_
#define SESSION_HH_

#include <vector>
#include <memory>

namespace skel { struct command; }

namespace skel {
struct session {
    void add(std::unique_ptr<command> c);
    void exec();

private:
    std::vector<std::unique_ptr<command>> work;
};
}  // namespace skel

#endif  // SESSION_HH_
