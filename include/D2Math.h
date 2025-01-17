#pragma once

#include <stdint.h>

#define D2Clamp(v, low, high) (((v) < (low)) ? (low) : ((high) < (v)) ? (high) : (v))

#define D2Lerp(v0, v1, t) (1 - (t)) * (v0) + (t) * (v1)

/*

template <typename T> inline constexpr
int32_t D2signum(T x, std::false_type is_signed) {
    return T(0) < x;
}

template <typename T> inline constexpr
int32_t D2signum(T x, std::true_type is_signed) {
    return (T(0) < x) - (x < T(0));
}

template <typename T> inline constexpr
int32_t D2signum(T x) {
    return D2signum(x, std::is_signed<T>());
}

*/