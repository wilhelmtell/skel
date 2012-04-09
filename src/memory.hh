#ifndef MEMORY_HH_
#define MEMORY_HH_

#include <memory>
#include <utility>

namespace mn {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}  // namespace skel

#endif  // MEMORY_HH_
