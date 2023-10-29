//
// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 10/14/23.
// Copyright (c) 2023 RobôCIn.
//

#pragma once

#include <iterator>
#include <type_traits>

namespace robocin::rect2d_internal {
template <class RT>
concept StructRect = requires(RT rect) {
                       rect.top_left;
                       rect.width;
                       rect.height;
                     };

template <class RT>
concept ClassRect = requires(RT rect) {
                      rect.TopLeft();
                      rect.Width();
                      rect.Height();
                    };

template <class RT>
class iterator {
  using rect_type = RT;
  using rect_pointer = rect_type*;

  template <class T>
  using dependent_const_t = std::conditional_t<std::is_const_v<rect_type>, const T, T>;

 public:
  // NOLINTNEXTLINE(readability-identifier-naming)
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = dependent_const_t<typename rect_type::value_type>;
  using pointer = value_type*;
  using reference = value_type&;

  // Constructors ----------------------------------------------------------------------------------
  constexpr iterator() = default;
  constexpr iterator(const iterator&) = default;
  constexpr iterator(iterator&&) noexcept = default;
  constexpr iterator(rect_pointer ptr, difference_type index) : ptr_(ptr), index_(index) {}

  // Assignment operators --------------------------------------------------------------------------
  constexpr iterator& operator=(const iterator&) = default;
  constexpr iterator& operator=(iterator&&) noexcept = default;

  // Destructor ------------------------------------------------------------------------------------
  constexpr ~iterator() = default;

  // Dereference operators -------------------------------------------------------------------------
  constexpr reference operator*() const {
    switch (index_) {
      case 0: return ptr_->top_left.x;
      case 1: return ptr_->top_left.y;
      case 2: return ptr_->width;
      case 3: return ptr_->height;
      default: throw std::out_of_range("Rect2D::iterator operator*: index out of range.");
    }
  }

  constexpr reference operator[](difference_type n) const {
    switch (index_ + n) {
      case 0: return ptr_->top_left.x;
      case 1: return ptr_->top_left.y;
      case 2: return ptr_->width;
      case 3: return ptr_->height;
      default: throw std::out_of_range("Rect2D::iterator operator[]: index out of range.");
    }
  }

  // Arithmetic-assignment operators ---------------------------------------------------------------
  constexpr iterator& operator+=(difference_type n) { return index_ += n, *this; }
  constexpr iterator& operator-=(difference_type n) { return index_ -= n, *this; }

  // Arithmetic operators --------------------------------------------------------------------------
  constexpr iterator operator+(difference_type n) const { return iterator(*this) += n; }
  constexpr iterator operator-(difference_type n) const { return iterator(*this) -= n; }

  constexpr difference_type operator-(const iterator& other) const { return index_ - other.index_; }

  // Arithmetic friend operator --------------------------------------------------------------------
  friend constexpr iterator operator+(difference_type n, const iterator& it) { return it + n; }

  // Increment and decrement operators -------------------------------------------------------------
  constexpr iterator& operator++() { return ++index_, *this; }
  constexpr iterator operator++(int) { // NOLINT(cert-dcl21-cpp)
    iterator result = *this;
    return ++index_, result;
  }

  constexpr iterator& operator--() { return --index_, *this; }
  constexpr iterator operator--(int) { // NOLINT(cert-dcl21-cpp)
    iterator result = *this;
    return --index_, result;
  }

  // Comparison operators --------------------------------------------------------------------------
  inline constexpr bool operator==(const iterator& other) const = default;
  inline constexpr auto operator<=>(const iterator& other) const = default;

 private:
  rect_pointer ptr_{nullptr};
  difference_type index_{0};
};

} // namespace robocin::rect2d_internal
