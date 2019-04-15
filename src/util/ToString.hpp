#pragma once
#include <string>
/**
 * A functor to apply std::to_string.
 * Usage enables a class template user to replace this
 * by another object to customize the transformation.
 */
namespace util
{
struct ToString
{
    template <typename T>
    std::string operator()(T&& n) {
        return std::to_string(std::forward<T>(n));
    }
};

} // namespace util end
