#ifndef COMMAND_HH_
#define COMMAND_HH_

namespace skel {
struct command {
    virtual ~command() = default;

    virtual void execute() const = 0;
};
}  // namespace skel

#endif  // COMMAND_HH_
