//
// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 10/14/23.
// Copyright (c) 2023 RobôCIn.
//

#pragma once

#include "robocin/geometry/internal/rect2d_internal.h"
#include "robocin/geometry/point2d.h"
#include "robocin/utility/epsilon.h"
#include "robocin/utility/fuzzy_compare.h"

#include <initializer_list>

namespace robocin {

template <typename T>
struct Rect2D {
 public:
  // Member types ----------------------------------------------------------------------------------
  using value_type = T;
  using reference = value_type&;
  using size_type = std::size_t;
  using iterator = rect2d_internal::iterator<Rect2D>;
  using const_iterator = rect2d_internal::iterator<const Rect2D>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // Friendships -----------------------------------------------------------------------------------
  template <class U>
  friend struct Rect2D;

  // Members ---------------------------------------------------------------------------------------
  Point2D<value_type> top_left;
  value_type width, height;

  // Static constructors ---------------------------------------------------------------------------
  static consteval Rect2D create() { return Rect2D(); }

  // Constructors ----------------------------------------------------------------------------------
  constexpr Rect2D() : top_left(0, 0), width{}, height{} {}
  constexpr Rect2D(const Rect2D& rect) = default;
  constexpr Rect2D(Rect2D&& rect) noexcept = default;

  constexpr Rect2D(const Point2D<value_type>& top_left, value_type width, value_type height) :
      top_left(top_left),
      width{width},
      height{height} {}

  constexpr Rect2D(Point2D<value_type>&& top_left, value_type width, value_type height) :
      top_left(top_left),
      width{width},
      height{height} {}

  constexpr Rect2D(const Point2D<value_type>& top_left, const Point2D<value_type>& bottom_right) :
      top_left(top_left),
      width{static_cast<value_type>(bottom_right.x - top_left.x)},
      height{static_cast<value_type>(bottom_right.y - top_left.y)} {}

  constexpr Rect2D(Point2D<value_type>&& top_left, Point2D<value_type>&& bottom_right) :
      top_left(top_left),
      width{static_cast<value_type>(bottom_right.x - top_left.x)},
      height{static_cast<value_type>(bottom_right.y - top_left.y)} {}
  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)

  constexpr explicit Rect2D(const rect2d_internal::StructRect auto& rect) :
      top_left(static_cast<Point2D<value_type>>(rect.top_left)),
      width{static_cast<value_type>(rect.width)},
      height{static_cast<value_type>(rect.height)} {}
  constexpr explicit Rect2D(const rect2d_internal::ClassRect auto& rect) :
      top_left(static_cast<Point2D<value_type>>(rect.TopLeft())),
      width{static_cast<value_type>(rect.Width())},
      height{static_cast<value_type>(rect.Height())} {}
  template <class U, class V>
  constexpr explicit Rect2D(const std::pair<U, V>& pair) :
      Rect2D(static_cast<Point2D<value_type>>(pair.first),
             static_cast<Point2D<value_type>>(pair.second)) {}

  // Destructor ------------------------------------------------------------------------------------
  constexpr ~Rect2D() = default;

  // Assignment operators --------------------------------------------------------------------------
  constexpr Rect2D& operator=(const Rect2D& other) = default;
  constexpr Rect2D& operator=(Rect2D&& other) noexcept = default;

  // Validators ------------------------------------------------------------------------------------
  [[nodiscard]] constexpr bool isNull() const {
    if constexpr (has_epsilon_v<value_type>) {
      return fuzzyIsZero(top_left.x) and fuzzyIsZero(top_left.y) and fuzzyIsZero(width)
             and fuzzyIsZero(height);
    } else {
      return top_left.x == 0 and top_left.y == 0 and width == 0 and height == 0;
    }
  }

  // Arithmetic-assignment operators ---------------------------------------------------------------
  inline constexpr Rect2D& operator+=(const Rect2D& other) {
    return top_left += other.top_left, width += other.width, height += other.height, *this;
  }
  inline constexpr Rect2D& operator-=(const Rect2D& other) {
    return top_left -= other.top_left, width -= other.width, height -= other.height, *this;
  }
  inline constexpr Rect2D& operator*=(value_type factor) {
    return width *= factor, height *= factor, *this;
  }
  inline constexpr Rect2D& operator/=(value_type factor) {
    return width /= factor, height /= factor, *this;
  }

  // Arithmetic operators --------------------------------------------------------------------------
  inline constexpr Rect2D operator+(const Rect2D& other) const { return Rect2D(*this) += other; }
  inline constexpr Rect2D operator-(const Rect2D& other) const { return Rect2D(*this) -= other; }
  inline constexpr Rect2D operator*(value_type factor) const { return Rect2D(*this) *= factor; }
  inline constexpr Rect2D operator/(value_type factor) const { return Rect2D(*this) /= factor; }

  // Arithmetic friend operators -------------------------------------------------------------------
  friend inline constexpr Rect2D operator*(value_type factor, const Rect2D& rect) {
    return Rect2D(rect.top_left, rect.width * factor, rect.height * factor);
  }

  // Sign operators --------------------------------------------------------------------------------
  inline constexpr Rect2D operator+() const { return *this; }
  inline constexpr Rect2D operator-() const { return Rect2D(-top_left, width, height); }

  // Comparison operators --------------------------------------------------------------------------
  inline constexpr bool operator==(const Rect2D& other) const {
    if constexpr (has_epsilon_v<value_type>) {
      return fuzzyCmpEqual(top_left.x, other.top_left.x)
             and fuzzyCmpEqual(top_left.y, other.top_left.y) and fuzzyCmpEqual(width, other.width)
             and fuzzyCmpEqual(height, other.height);
    } else {
      return top_left.x == other.top_left.x and top_left.y == other.top_left.y
             and width == other.width and height == other.height;
    }
  }

  inline constexpr bool contains(const Point2D<value_type>& point) const {
    return top_left.x <= point.x and point.x <= (top_left.x + width) and point.y >= top_left.y
           and point.y <= (top_left.y + height);
  }

  inline constexpr bool contains(const Rect2D& rect) const {
    return this->contains(rect.top_left)
           and this->contains(
               Point2D<value_type>(rect.top_left.x + rect.width, rect.top_left.y + rect.height));
  }

  inline constexpr bool intersects(const Rect2D& other) const {
    return this->contains(other.top_left) or other.contains(this->top_left);
  }

  // Swap ------------------------------------------------------------------------------------------
  constexpr void swap(Rect2D& other) noexcept { std::swap(*this, other); }

  // Array-like ------------------------------------------------------------------------------------
  [[nodiscard]] static consteval size_type size() { return 4; }

  inline constexpr reference operator[](size_type pos) {
    switch (pos) {
      case 0: return top_left.x;
      case 1: return top_left.y;
      case 2: return width;
      case 3: return height;
      default: throw std::out_of_range("Rect2D operator[]: index out of range.");
    }
  }

  inline constexpr value_type operator[](size_type pos) const {
    switch (pos) {
      case 0: return top_left.x;
      case 1: return top_left.y;
      case 2: return width;
      case 3: return height;
      default: throw std::out_of_range("Rect2D operator[]: index out of range.");
    }
  }

  // Iterators -------------------------------------------------------------------------------------
  constexpr iterator begin() noexcept { return iterator{this, /*index=*/0}; }
  [[nodiscard]] constexpr const_iterator begin() const noexcept {
    return const_iterator{this, /*index=*/0};
  }
  constexpr iterator end() noexcept { return iterator{this, size()}; }
  [[nodiscard]] constexpr const_iterator end() const noexcept {
    return const_iterator{this, size()};
  }

  constexpr reverse_iterator rbegin() noexcept { return reverse_iterator{end()}; }
  [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator{end()};
  }
  constexpr reverse_iterator rend() noexcept { return reverse_iterator{begin()}; }
  [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator{begin()};
  }

  [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
    return const_iterator{this, /*index=*/0};
  }
  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return const_iterator{this, size()};
  }
  [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator{end()};
  }
  [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator{begin()};
  }

  // Input/Output operators ------------------------------------------------------------------------
  friend inline std::istream& operator>>(std::istream& is, Rect2D& rect) {
    return is >> rect.top_left.x >> rect.top_left.y >> rect.width >> rect.height;
  }

  friend inline std::ostream& operator<<(std::ostream& os, const Rect2D& rect) {
    return os << "[.top_left = " << rect.top_left << ", .width = " << rect.width
              << ", .height = " << rect.height << " ]";
  }
};

// Deduction guides --------------------------------------------------------------------------------
Rect2D()->Rect2D<double>;

template <class T, class U>
Rect2D(T, U) -> Rect2D<std::common_type_t<T, U>>;

} // namespace robocin
