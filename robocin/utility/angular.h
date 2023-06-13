//
// Created by José Cruz <joseviccruz> on 24/02/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_UTILITY_ANGULAR_H
#define ROBOCIN_UTILITY_ANGULAR_H

#include <cmath>
#include <cstdint>
#include <numbers>

#include "robocin/utility/concepts.h"

#include "robocin/utility/internal/angular_internal.h"

namespace robocin {

template <arithmetic T>
constexpr auto degreesToRadians(T degrees) {
  using F = std::conditional_t<std::floating_point<T>, T, double>;

  constexpr F kDegreesToRadiansFactor = std::numbers::pi_v<F> / 180;

  return degrees * kDegreesToRadiansFactor;
}

template <arithmetic T>
constexpr auto radiansToDegrees(T radians) {
  using F = std::conditional_t<std::floating_point<T>, T, double>;

  constexpr F kRadiansToDegreesFactor = 180 / std::numbers::pi_v<F>;

  return radians * kRadiansToDegreesFactor;
}

template <arithmetic T>
constexpr auto normalizeAngle(T angle) {
  using F = std::conditional_t<std::floating_point<T>, T, double>;

  constexpr F kPi = std::numbers::pi_v<F>;
  constexpr F k2Pi = 2 * kPi;

  if (-kPi <= angle && angle <= kPi) {
    return static_cast<F>(angle);
  }

  F result = std::fmod(static_cast<F>(angle), k2Pi);
  if (result < -kPi) {
    result += k2Pi;
  } else if (result > kPi) {
    result -= k2Pi;
  }
  return result;
}

template <arithmetic T, arithmetic U>
constexpr auto smallestAngleDiff(T lhs, U rhs) {
  using F = std::conditional_t<std::floating_point<std::common_type_t<T, U>>, T, double>;

  return normalizeAngle<F>(rhs - lhs);
}

template <arithmetic T, arithmetic U>
constexpr auto absSmallestAngleDiff(T lhs, U rhs) {
  return std::abs(smallestAngleDiff(lhs, rhs));
}

template <arithmetic T>
constexpr auto fsin(T radians) { // NOLINT(readability-identifier-naming)
  using F = std::conditional_t<std::floating_point<T>, T, double>;

  auto index = static_cast<int>(2 * radiansToDegrees(normalizeAngle(radians)));

  // since sin is an odd function, i.e. sin(x) = -sin(-x), we can use the absolute value:
  if (index < 0) {
    return -angular_internal::kSinTable<F>[-index];
  }
  return angular_internal::kSinTable<F>[index];
}

template <arithmetic T>
constexpr auto fcos(T radians) { // NOLINT(readability-identifier-naming)
  using F = std::conditional_t<std::floating_point<T>, T, double>;

  auto index = static_cast<int>(2 * radiansToDegrees(normalizeAngle(radians)));

  // since cos is an even function, i.e. cos(x) = cos(-x), we can use the absolute value:
  if (index < 0) {
    return angular_internal::kCosTable<F>[-index];
  }
  return angular_internal::kCosTable<F>[index];
}

} // namespace robocin

#endif // ROBOCIN_UTILITY_ANGULAR_H
