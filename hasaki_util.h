#ifndef __HASAKI_UTIL_H__
#define __HASAKI_UTIL_H__

#include <type_traits>

template <typename T>
std::enable_if<std::is_integral<T>::type, bool> IsOdd(T t) {
    return (bool)(t % 2);
}

#endif