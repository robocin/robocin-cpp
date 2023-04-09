//
// Created by José Cruz <joseviccruz> on 08/04/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_UTILITY_FUZZY_COMPARE_H
#define ROBOCIN_UTILITY_FUZZY_COMPARE_H

#include <cmath>
#include <compare>
#include <concepts>

#include "robocin/utility/concepts.h"
#include "robocin/utility/epsilon.h"

namespace robocin {

// Compare if a given value is zero, using a given epsilon -----------------------------------------
template <arithmetic T, std::floating_point U>
constexpr bool fuzzyIsZero(T value, U epsilon) {
  return std::abs(value) <= epsilon;
}

// Compare if a given value is zero, using the injected epsilon ------------------------------------
template <arithmetic T, std::floating_point U = T>
constexpr bool fuzzyIsZero(T value)
  requires(has_epsilon_v<U>)
{
  return fuzzyIsZero(value, epsilon_v<U>);
}

// Compare if two given values are equal, using a given epsilon ------------------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpEqual(T lhs, U rhs, V epsilon) {
  return std::abs(lhs - rhs) <= epsilon;
}

// Compare if two given values are equal, using the injected epsilon -------------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpEqual(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return fuzzyCmpEqual(lhs, rhs, epsilon_v<V>);
}

// Compare if two given values are not equal, using a given epsilon --------------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpNotEqual(T lhs, U rhs, V epsilon) {
  return not fuzzyCmpEqual(lhs, rhs, epsilon);
}

// Compare if two given values are not equal, using the injected epsilon ---------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpNotEqual(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return not fuzzyCmpEqual(lhs, rhs, epsilon_v<V>);
}

// Three-way compare two given values, using a given epsilon ---------------------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr std::strong_ordering fuzzyCmpThreeWay(T lhs, U rhs, V epsilon) {
  if (fuzzyCmpEqual(lhs, rhs, epsilon)) {
    return std::strong_ordering::equal;
  }
  return (lhs < rhs) ? std::strong_ordering::less : std::strong_ordering::greater;
}

// Three-way compare two given values, using the injected epsilon ----------------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr std::strong_ordering fuzzyCmpThreeWay(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return fuzzyCmpThreeWay(lhs, rhs, epsilon_v<V>);
}

// Compare if the first given value is lt the second, using a given epsilon ------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpLess(T lhs, U rhs, V epsilon) {
  return std::is_lt(fuzzyCmpThreeWay(lhs, rhs, epsilon));
}

// Compare if the first given value lt than the second, using the injected epsilon -----------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpLess(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return fuzzyCmpLess(lhs, rhs, epsilon_v<V>);
}

// Compare if the first given value is lteq to the second, using a given epsilon -------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpLessEqual(T lhs, U rhs, V epsilon) {
  return std::is_lteq(fuzzyCmpThreeWay(lhs, rhs, epsilon));
}

// Compare if the first given value is lteq to the second, using the injected epsilon --------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpLessEqual(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return fuzzyCmpLessEqual(lhs, rhs, epsilon_v<V>);
}

// Compare if the first given value is gt the second, using a given epsilon ------------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpGreater(T lhs, U rhs, V epsilon) {
  return std::is_gt(fuzzyCmpThreeWay(lhs, rhs, epsilon));
}

// Compare if the first given value is gt the second, using the injected epsilon -------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpGreater(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return fuzzyCmpGreater(lhs, rhs, epsilon_v<V>);
}

// Compare if the first given value is gteq to the second, using a given epsilon -------------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpGreaterEqual(T lhs, U rhs, V epsilon) {
  return std::is_gteq(fuzzyCmpThreeWay(lhs, rhs, epsilon));
}

// Compare if the first given value is gteq to the second, using the injected epsilon --------------
template <arithmetic T, arithmetic U, std::floating_point V = std::common_type_t<T, U>>
constexpr bool fuzzyCmpGreaterEqual(T lhs, U rhs)
  requires(has_epsilon_v<V>)
{
  return fuzzyCmpGreaterEqual(lhs, rhs, epsilon_v<V>);
}

// Functors ----------------------------------------------------------------------------------------
template <class F>
class FuzzyIsZero {
 public:
  using floating_point_type = F;

  constexpr FuzzyIsZero() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyIsZero(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type value) const noexcept {
    return fuzzyIsZero(value, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyEqualTo {
 public:
  using floating_point_type = F;

  constexpr FuzzyEqualTo() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyEqualTo(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type lhs, floating_point_type rhs) const noexcept {
    return fuzzyCmpEqual(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyNotEqualTo {
 public:
  using floating_point_type = F;

  constexpr FuzzyNotEqualTo() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyNotEqualTo(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type lhs, floating_point_type rhs) const noexcept {
    return fuzzyCmpNotEqual(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyThreeWay {
 public:
  using floating_point_type = F;

  constexpr FuzzyThreeWay() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyThreeWay(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr std::strong_ordering operator()(floating_point_type lhs,
                                            floating_point_type rhs) const noexcept {
    return fuzzyCmpThreeWay(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyLess {
 public:
  using floating_point_type = F;

  constexpr FuzzyLess() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyLess(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type lhs, floating_point_type rhs) const noexcept {
    return fuzzyCmpLess(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyLessEqual {
 public:
  using floating_point_type = F;

  constexpr FuzzyLessEqual() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyLessEqual(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type lhs, floating_point_type rhs) const noexcept {
    return fuzzyCmpLessEqual(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyGreater {
 public:
  using floating_point_type = F;

  constexpr FuzzyGreater() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyGreater(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type lhs, floating_point_type rhs) const noexcept {
    return fuzzyCmpGreater(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

template <class F>
class FuzzyGreaterEqual {
 public:
  using floating_point_type = F;

  constexpr FuzzyGreaterEqual() noexcept
    requires(has_epsilon_v<floating_point_type>)
      : epsilon_{epsilon_v<floating_point_type>} {}

  constexpr explicit FuzzyGreaterEqual(floating_point_type epsilon) noexcept : epsilon_{epsilon} {}

  constexpr bool operator()(floating_point_type lhs, floating_point_type rhs) const noexcept {
    return fuzzyCmpGreaterEqual(lhs, rhs, epsilon_);
  }

 private:
  floating_point_type epsilon_;
};

} // namespace robocin

#endif // ROBOCIN_UTILITY_FUZZY_COMPARE_H
