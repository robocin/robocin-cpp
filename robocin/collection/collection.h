//
// Created by José Cruz <joseviccruz> on 27/03/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_COLLECTION_COLLECTION_H
#define ROBOCIN_COLLECTION_COLLECTION_H

#include "robocin/collection/internal/collection_internal.h"

#include <algorithm>
#include <array>
#include <execution>
#include <functional>
#include <iterator>
#include <ranges>
#include <vector>

namespace robocin {

template <class T, class Container = std::vector<T>>
class Collection {
 public:
  // Member types ----------------------------------------------------------------------------------
  using container_type = Container;

  using value_type = typename container_type::value_type;
  using size_type = typename container_type::size_type;

  using reference = typename container_type::reference;
  using const_reference = typename container_type::const_reference;

  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  // Friendships -----------------------------------------------------------------------------------
  template <class U, class C>
  friend class Collection;

  // Constructors ----------------------------------------------------------------------------------
  constexpr Collection() = default;
  constexpr Collection(const Collection& other) = default;
  constexpr Collection(Collection&& other) noexcept = default;

  constexpr explicit Collection(size_type count) : container_(count) {}
  constexpr Collection(size_type count, const value_type& value) : container_(count, value) {}

  constexpr Collection(std::initializer_list<value_type> il) : container_(il) {}
  constexpr explicit Collection(const container_type& container) : container_(container) {}
  constexpr explicit Collection(container_type&& container) : container_(std::move(container)) {}

  template <class FirstIt, class LastIt>
  constexpr Collection(FirstIt first, LastIt last) : container_(first, last) {}

  template <std::ranges::range R>
  constexpr explicit Collection(R&& range) : // NOLINT(bugprone-forwarding-reference-overload)
      Collection(std::begin(std::forward<R>(range)), std::end(std::forward<R>(range))) {}

  // Destructor ------------------------------------------------------------------------------------
  constexpr ~Collection() = default;

  // Assignment operators --------------------------------------------------------------------------
  constexpr Collection& operator=(const Collection& other) = default;
  constexpr Collection& operator=(Collection&& other) noexcept = default;

  // NOLINTBEGIN(*-assign*)
  constexpr Collection& operator=(std::initializer_list<value_type> il) {
    return container_ = il, *this;
  }
  constexpr Collection& operator=(const container_type& container) {
    return container_ = container, *this;
  }
  constexpr Collection& operator=(container_type&& container) {
    return container_ = std::move(container), *this;
  }
  template <std::ranges::range R>
  constexpr Collection& operator=(R&& range) {
    return *this = Collection(std::forward<R>(range));
  }
  // NOLINTEND(*-assign*)

  // Element access --------------------------------------------------------------------------------
  constexpr reference at(size_type pos) { return container_.at(pos); }
  constexpr const_reference at(size_type pos) const { return container_.at(pos); }
  constexpr reference operator[](size_type pos) { return container_[pos]; }
  constexpr const_reference operator[](size_type pos) const { return container_[pos]; }
  constexpr reference front() { return container_.front(); }
  constexpr const_reference front() const { return container_.front(); }
  constexpr reference back() { return container_.back(); }
  constexpr const_reference back() const { return container_.back(); }

  // Capacity --------------------------------------------------------------------------------------
  [[nodiscard]] constexpr bool empty() const { return container_.empty(); }
  constexpr size_type size() const { return container_.size(); }
  constexpr size_type max_size() const { return container_.max_size(); } // NOLINT(*-naming*)
  constexpr void reserve(size_type new_cap) { container_.reserve(new_cap); }
  constexpr size_type capacity() const { return container_.capacity(); }
  constexpr void shrink_to_fit() { container_.shrink_to_fit(); } // NOLINT(*-naming*)

  // Modifiers -------------------------------------------------------------------------------------
  // NOLINTBEGIN(*-naming*)
  constexpr void append_range(const Collection& other) {
    container_.insert(container_.end(), other.container_.begin(), other.container_.end());
  }
  constexpr void append_range(Collection&& other) { // NOLINT(*-rvalue*)
    container_.insert(container_.end(),
                      std::make_move_iterator(other.container_.begin()),
                      std::make_move_iterator(other.container_.end()));
  }
  constexpr void append_range(std::initializer_list<value_type> il) {
    container_.insert(container_.end(), il);
  }
  template <std::ranges::range R>
  constexpr void append_range(R&& range) {
    container_.insert(container_.end(),
                      std::begin(std::forward<R>(range)),
                      std::end(std::forward<R>(range)));
  }
  // NOLINTEND(*-naming*)

  constexpr void clear() { container_.clear(); }

  template <class... Args>
  constexpr iterator emplace(Args&&... args) {
    return container_.emplace(std::forward<Args>(args)...);
  }

  template <class... Args> // NOLINTNEXTLINE(*-naming*)
  constexpr reference emplace_back(Args&&... args) {
    return container_.emplace_back(std::forward<Args>(args)...);
  }

  constexpr void erase(const_iterator pos) { container_.erase(pos); }
  constexpr void erase(const_iterator first, const_iterator last) { container_.erase(first, last); }

  constexpr iterator insert(const_iterator pos, const value_type& value) {
    return container_.insert(pos, value);
  }
  constexpr iterator insert(const_iterator pos, value_type&& value) {
    return container_.insert(pos, std::move(value));
  }
  constexpr iterator insert(const_iterator pos, size_type count, const value_type& value) {
    return container_.insert(pos, count, value);
  }
  template <class FirstIt, class LastIt>
  constexpr iterator insert(const_iterator pos, FirstIt first, LastIt last) {
    return container_.insert(pos, first, last);
  }
  constexpr iterator insert(const_iterator pos, std::initializer_list<value_type> il) {
    return container_.insert(pos, il);
  }
  template <std::ranges::range R>
  constexpr iterator insert(const_iterator pos, R&& range) {
    return container_.insert(pos,
                             std::begin(std::forward<R>(range)),
                             std::end(std::forward<R>(range)));
  }

  constexpr void push_back(const value_type& value) // NOLINT(*-naming*)
  {
    container_.push_back(value);
  }
  constexpr void push_back(value_type&& value) // NOLINT(*-naming*)
  {
    container_.push_back(std::move(value));
  }

  constexpr void pop_back() { container_.pop_back(); } // NOLINT(*-naming*)

  constexpr void resize(size_type count) { container_.resize(count); }
  constexpr void resize(size_type count, const value_type& value) {
    container_.resize(count, value);
  }

  constexpr Collection resized(size_type count) && {
    return container_.resize(count), std::move(*this);
  }
  constexpr Collection resized(size_type count) const& { return Collection(*this).resized(count); }

  constexpr Collection resized(size_type count, const value_type& value) && {
    return container_.resize(count, value), std::move(*this);
  }
  constexpr Collection resized(size_type count, const value_type& value) const& {
    return Collection(*this).resized(count, value);
  }

  constexpr void swap(Collection& other) { container_.swap(other.container_); }

  // Comparison operators --------------------------------------------------------------------------
  inline constexpr bool operator==(const Collection& other) const {
    return container_ == other.container_;
  }
  inline constexpr auto operator<=>(const Collection& other) const {
    return container_ <=> other.container_;
  }

  // Iterators -------------------------------------------------------------------------------------
  constexpr iterator begin() noexcept { return container_.begin(); }
  constexpr const_iterator begin() const noexcept { return container_.begin(); }
  constexpr iterator end() noexcept { return container_.end(); }
  constexpr const_iterator end() const noexcept { return container_.end(); }

  constexpr reverse_iterator rbegin() noexcept { return container_.rbegin(); }
  constexpr const_reverse_iterator rbegin() const noexcept { return container_.rbegin(); }
  constexpr reverse_iterator rend() noexcept { return container_.rend(); }
  constexpr const_reverse_iterator rend() const noexcept { return container_.rend(); }

  constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
  constexpr const_iterator cend() const noexcept { return container_.cend(); }
  constexpr const_reverse_iterator crbegin() const noexcept { return container_.crbegin(); }
  constexpr const_reverse_iterator crend() const noexcept { return container_.crend(); }

  // Reduce ----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class BinaryOperation>
  [[nodiscard]] constexpr value_type
  reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) && {
    return std::reduce(std::forward<ExecutionPolicy>(policy),
                       std::make_move_iterator(container_.begin()),
                       std::make_move_iterator(container_.end()),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }
  template <class ExecutionPolicy, class BinaryOperation>
  [[nodiscard]] constexpr value_type
  reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) const& {
    return std::reduce(std::forward<ExecutionPolicy>(policy),
                       container_.begin(),
                       container_.end(),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }

  template <class BinaryOperation>
  [[nodiscard]] constexpr value_type reduce(BinaryOperation&& op, value_type init) && {
    return std::reduce(std::make_move_iterator(container_.begin()),
                       std::make_move_iterator(container_.end()),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }
  template <class BinaryOperation>
  [[nodiscard]] constexpr value_type reduce(BinaryOperation&& op, value_type init) const& {
    return std::reduce(container_.begin(),
                       container_.end(),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }

  // Filter ----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class UnaryPredicate>
  constexpr void filter(ExecutionPolicy&& policy, UnaryPredicate&& predicate) & {
    iterator last = std::remove_if(std::forward<ExecutionPolicy>(policy),
                                   container_.begin(),
                                   container_.end(),
                                   std::not_fn(std::forward<UnaryPredicate>(predicate)));

    container_.erase(last, container_.end());
  }
  template <class ExecutionPolicy, class UnaryPredicate>
  [[nodiscard]] constexpr Collection filtered(ExecutionPolicy&& policy,
                                              UnaryPredicate&& predicate) && {
    filter(std::forward<ExecutionPolicy>(policy), std::forward<UnaryPredicate>(predicate));
    return std::move(*this);
  }
  template <class ExecutionPolicy, class UnaryPredicate>
  [[nodiscard]] constexpr Collection filtered(ExecutionPolicy&& policy,
                                              UnaryPredicate&& predicate) const& {
    return Collection(*this).filtered(std::forward<ExecutionPolicy>(policy),
                                      std::forward<UnaryPredicate>(predicate));
  }

  template <class UnaryPredicate>
  constexpr void filter(UnaryPredicate&& predicate) & {
    iterator last = std::remove_if(container_.begin(),
                                   container_.end(),
                                   std::not_fn(std::forward<UnaryPredicate>(predicate)));

    container_.erase(last, container_.end());
  }
  template <class UnaryPredicate>
  [[nodiscard]] constexpr Collection filtered(UnaryPredicate&& predicate) && {
    return filter(std::forward<UnaryPredicate>(predicate)), std::move(*this);
  }
  template <class UnaryPredicate>
  [[nodiscard]] constexpr Collection filtered(UnaryPredicate&& predicate) const& {
    return Collection(*this).filtered(std::forward<UnaryPredicate>(predicate));
  }

  // Transform -------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class UnaryOperation>
  [[nodiscard]] constexpr auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) && {
    using result_type = std::invoke_result_t<UnaryOperation, value_type>;

    if constexpr (std::is_same_v<result_type, value_type>) {
      std::for_each(std::forward<ExecutionPolicy>(policy),
                    container_.begin(),
                    container_.end(),
                    [map_value = std::forward<UnaryOperation>(op)](value_type& value) {
                      value = std::move(map_value(value));
                    });

      return std::move(*this);
    } else {
      collection_internal::ResultCollection<container_type, result_type> result(container_.size());

      std::transform(std::forward<ExecutionPolicy>(policy),
                     std::make_move_iterator(container_.begin()),
                     std::make_move_iterator(container_.end()),
                     result.begin(),
                     std::forward<UnaryOperation>(op));

      return result;
    }
  }
  template <class ExecutionPolicy, class UnaryOperation>
  [[nodiscard]] constexpr auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) const& {
    return Collection(*this).transform(std::forward<ExecutionPolicy>(policy),
                                       std::forward<UnaryOperation>(op));
  }

  template <class UnaryOperation>
  [[nodiscard]] constexpr auto transform(UnaryOperation&& op) && {
    using result_type = std::invoke_result_t<UnaryOperation, value_type>;

    if constexpr (std::is_same_v<result_type, value_type>) {
      auto&& map_value = std::forward<UnaryOperation>(op);
      for (value_type& value : container_) {
        value = std::move(map_value(value));
      }
      return std::move(*this);
    } else {
      collection_internal::ResultCollection<container_type, result_type> result;
      result.reserve(container_.size());

      std::transform(std::make_move_iterator(container_.begin()),
                     std::make_move_iterator(container_.end()),
                     std::back_inserter(result.container_),
                     std::forward<UnaryOperation>(op));

      return result;
    }
  }
  template <class UnaryOperation>
  [[nodiscard]] constexpr auto transform(UnaryOperation&& op) const& {
    return Collection(*this).transform(std::forward<UnaryOperation>(op));
  }

  // Flat transform --------------------------------------------------------------------------------
  // NOLINTBEGIN(*-naming*)
  template <class ExecutionPolicy, class UnaryOperation>
    requires(std::ranges::range<value_type>)
  [[nodiscard]] constexpr auto flat_transform(ExecutionPolicy&& policy, UnaryOperation&& op) && {
    using input_type = std::ranges::range_value_t<value_type>;
    using result_type = std::invoke_result_t<UnaryOperation, input_type>;

    auto&& pol = std::forward<ExecutionPolicy>(policy);

    auto sizes_view = std::views::transform(container_, std::size<value_type>);
    size_type result_size = std::reduce(pol, sizes_view.begin(), sizes_view.end(), size_type{0});

    collection_internal::ResultCollection<container_type, result_type> result(result_size);
    auto&& out = result.begin();

    auto&& fun = std::forward<UnaryOperation>(op);

    for (auto&& element : container_) {
      out = std::transform(pol,
                           std::make_move_iterator(std::begin(element)),
                           std::make_move_iterator(std::end(element)),
                           out,
                           fun);
    }

    return result;
  }
  template <class ExecutionPolicy, class UnaryOperation>
    requires(std::ranges::range<value_type>)
  [[nodiscard]] constexpr auto flat_transform(ExecutionPolicy&& policy,
                                              UnaryOperation&& op) const& {
    return Collection(*this).flat_transform(std::forward<ExecutionPolicy>(policy),
                                            std::forward<UnaryOperation>(op));
  }

  template <class UnaryOperation>
    requires(std::ranges::range<value_type>)
  [[nodiscard]] constexpr auto flat_transform(UnaryOperation&& op) && {
    using input_type = std::ranges::range_value_t<value_type>;
    using result_type = std::invoke_result_t<UnaryOperation, input_type>;

    auto sizes_view = std::views::transform(container_, std::size<value_type>);
    size_type result_size = std::reduce(sizes_view.begin(), sizes_view.end(), size_type{0});

    collection_internal::ResultCollection<container_type, result_type> result;
    result.reserve(result_size);

    auto&& fun = std::forward<UnaryOperation>(op);
    for (auto&& element : container_) {
      auto&& transformed = std::views::transform(element, fun);
      result.insert(result.end(),
                    std::make_move_iterator(std::begin(transformed)),
                    std::make_move_iterator(std::end(transformed)));
    }

    return result;
  }
  template <class UnaryOperation>
    requires(std::ranges::range<value_type>)
  [[nodiscard]] constexpr auto flat_transform(UnaryOperation&& op) const& {
    return Collection(*this).flat_transform(std::forward<UnaryOperation>(op));
  }
  // NOLINTEND(*-naming*)

  // Sorts -----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class Cmp>
  constexpr void sort(ExecutionPolicy&& policy, Cmp cmp) & {
    std::sort(std::forward<ExecutionPolicy>(policy), container_.begin(), container_.end(), cmp);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection sorted(ExecutionPolicy&& policy, Cmp cmp) && {
    return sort(std::forward<ExecutionPolicy>(policy), cmp), std::move(*this);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection sorted(ExecutionPolicy&& policy, Cmp cmp) const& {
    return Collection(*this).sorted(std::forward<ExecutionPolicy>(policy), cmp);
  }

  template <class Cmp = std::ranges::less>
  constexpr void sort(Cmp cmp = {}) & {
    std::ranges::sort(container_, cmp);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection sorted(Cmp cmp = {}) && {
    return sort(cmp), std::move(*this);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection sorted(Cmp cmp = {}) const& {
    return Collection(*this).sorted(cmp);
  }

  // NOLINTBEGIN(*-naming*)
  template <class ExecutionPolicy, class Cmp>
  constexpr void stable_sort(ExecutionPolicy&& policy, Cmp cmp) & {
    std::stable_sort(std::forward<ExecutionPolicy>(policy),
                     container_.begin(),
                     container_.end(),
                     cmp);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection stable_sorted(ExecutionPolicy&& policy, Cmp cmp) && {
    return stable_sort(std::forward<ExecutionPolicy>(policy), cmp), std::move(*this);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection stable_sorted(ExecutionPolicy&& policy, Cmp cmp) const& {
    return Collection(*this).stable_sorted(std::forward<ExecutionPolicy>(policy), cmp);
  }

  template <class Cmp = std::ranges::less>
  constexpr void stable_sort(Cmp cmp = {}) & {
    std::ranges::stable_sort(container_, cmp);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection stable_sorted(Cmp cmp = {}) && {
    return stable_sort(cmp), std::move(*this);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection stable_sorted(Cmp cmp = {}) const& {
    return Collection(*this).stable_sorted(cmp);
  }
  // NOLINTEND(*-naming*)

  // Reverse ---------------------------------------------------------------------------------------
  template <class ExecutionPolicy>
  constexpr void reverse(ExecutionPolicy&& policy) & {
    std::reverse(std::forward<ExecutionPolicy>(policy), container_.begin(), container_.end());
  }
  template <class ExecutionPolicy>
  [[nodiscard]] constexpr Collection reversed(ExecutionPolicy&& policy) && {
    return reverse(std::forward<ExecutionPolicy>(policy)), std::move(*this);
  }
  template <class ExecutionPolicy>
  [[nodiscard]] constexpr Collection reversed(ExecutionPolicy&& policy) const& {
    return Collection(*this).reversed(std::forward<ExecutionPolicy>(policy));
  }

  constexpr void reverse() & { std::ranges::reverse(container_); }
  [[nodiscard]] constexpr Collection reversed() && { return reverse(), std::move(*this); }
  [[nodiscard]] constexpr Collection reversed() const& { return Collection(*this).reversed(); }

  // Contains --------------------------------------------------------------------------------------
  template <class ExecutionPolicy>
  constexpr bool contains(ExecutionPolicy&& policy, const value_type& value) const {
    return std::find(std::forward<ExecutionPolicy>(policy),
                     container_.begin(),
                     container_.end(),
                     value)
           != container_.end();
  }

  template <class ExecutionPolicy, class U>
  constexpr bool contains(ExecutionPolicy&& policy, const U& value) const {
    return std::find(std::forward<ExecutionPolicy>(policy),
                     container_.begin(),
                     container_.end(),
                     value)
           != container_.end();
  }

  constexpr bool contains(const value_type& value) const {
    return std::ranges::find(container_, value) != container_.end();
  }

  template <class U>
  constexpr bool contains(const U& value) const {
    return std::ranges::find(container_, value) != container_.end();
  }

  // Implicit conversions --------------------------------------------------------------------------
  constexpr explicit operator bool() const noexcept { return not container_.empty(); }

  constexpr operator container_type() const& { return container_; }        // NOLINT(*-explicit*)
  constexpr operator container_type() && { return std::move(container_); } // NOLINT(*-explicit*)

  template <std::ranges::range R>
  constexpr operator R() const& { // NOLINT(*-explicit*)
    return R(container_.begin(), container_.end());
  }
  template <std::ranges::range R>
  constexpr operator R() && { // NOLINT(*-explicit*)
    return R(std::make_move_iterator(container_.begin()),
             std::make_move_iterator(container_.end()));
  }

  template <class F, class S>
  constexpr operator std::pair<F, S>() const& { // NOLINT(*-explicit*)
    value_type first{};
    value_type second{};
    if (const_iterator it = container_.begin(); it != container_.end()) {
      first = *it;
      if (++it != end()) {
        second = *it;
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }
  template <class F, class S>
  constexpr operator std::pair<F, S>() && { // NOLINT(*-explicit*)
    value_type first{};
    value_type second{};
    if (iterator it = container_.begin(); it != container_.end()) {
      first = std::move(*it);
      if (++it != end()) {
        second = std::move(*it);
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }

  template <class... Ts>
  constexpr operator std::tuple<Ts...>() const& { // NOLINT(*-explicit*)
    std::tuple<Ts...> result{};
    collection_internal::assign(result, *this);
    return result;
  }
  template <class... Ts>
  constexpr operator std::tuple<Ts...>() && { // NOLINT(*-explicit*)
    std::tuple<Ts...> result{};
    collection_internal::assign(result, std::move(*this));
    return result;
  }

 private:
  container_type container_;
};

// Specialization for std::array -------------------------------------------------------------------
template <class T, std::size_t N>
class Collection<T, std::array<T, N>> {
 public:
  // Member types ----------------------------------------------------------------------------------
  using container_type = std::array<T, N>;

  using value_type = typename container_type::value_type;
  using size_type = typename container_type::size_type;

  using reference = typename container_type::reference;
  using const_reference = typename container_type::const_reference;

  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  // Constructors ----------------------------------------------------------------------------------
  constexpr Collection() = default;
  constexpr Collection(const Collection& other) = default;
  constexpr Collection(Collection&& other) noexcept = default;

  constexpr explicit Collection(const container_type& container) : container_(container) {}
  constexpr explicit Collection(container_type&& container) noexcept :
      container_(std::move(container)) {}

  template <class FirstIt, class LastIt>
  constexpr Collection(FirstIt first, LastIt last) {
    for (iterator it = container_.begin(); first != last && it != container_.end(); ++it, ++first) {
      *it = std::move(*first);
    }
  }

  constexpr Collection(std::initializer_list<value_type> il) : Collection(il.begin(), il.end()) {}

  template <std::ranges::range R>
  constexpr explicit Collection(R&& range) : // NOLINT(bugprone-forwarding-reference-overload)
      Collection(std::begin(std::forward<R>(range)), std::end(std::forward<R>(range))) {}

  // Destructor ------------------------------------------------------------------------------------
  constexpr ~Collection() = default;

  // Assignment operators --------------------------------------------------------------------------
  constexpr Collection& operator=(const Collection& other) = default;
  constexpr Collection& operator=(Collection&& other) noexcept = default;

  // NOLINTBEGIN(*-assign*)
  constexpr Collection& operator=(std::initializer_list<value_type> il) {
    return container_ = il, *this;
  }
  constexpr Collection& operator=(const container_type& container) {
    return container_ = container, *this;
  }
  constexpr Collection& operator=(container_type&& container) {
    return container_ = std::move(container), *this;
  }
  template <std::ranges::range R>
  constexpr Collection& operator=(R&& range) {
    return *this = Collection(std::forward<R>(range));
  }
  // NOLINTEND(*-assign*)

  // Element access --------------------------------------------------------------------------------
  constexpr reference at(size_type pos) { return container_.at(pos); }
  constexpr const_reference at(size_type pos) const { return container_.at(pos); }
  constexpr reference operator[](size_type pos) { return container_[pos]; }
  constexpr const_reference operator[](size_type pos) const { return container_[pos]; }
  constexpr reference front() { return container_.front(); }
  constexpr const_reference front() const { return container_.front(); }
  constexpr reference back() { return container_.back(); }
  constexpr const_reference back() const { return container_.back(); }

  // Capacity --------------------------------------------------------------------------------------
  [[nodiscard]] constexpr bool empty() const { return container_.empty(); }
  constexpr size_type size() const { return container_.size(); }

  // Modifiers -------------------------------------------------------------------------------------
  constexpr void swap(Collection& other) { container_.swap(other.container_); }

  // Comparison operators --------------------------------------------------------------------------
  inline constexpr bool operator==(const Collection& other) const {
    return container_ == other.container_;
  }
  inline constexpr auto operator<=>(const Collection& other) const {
    return container_ <=> other.container_;
  }

  // Iterators -------------------------------------------------------------------------------------
  constexpr iterator begin() noexcept { return container_.begin(); }
  constexpr const_iterator begin() const noexcept { return container_.begin(); }
  constexpr iterator end() noexcept { return container_.end(); }
  constexpr const_iterator end() const noexcept { return container_.end(); }

  constexpr reverse_iterator rbegin() noexcept { return container_.rbegin(); }
  constexpr const_reverse_iterator rbegin() const noexcept { return container_.rbegin(); }
  constexpr reverse_iterator rend() noexcept { return container_.rend(); }
  constexpr const_reverse_iterator rend() const noexcept { return container_.rend(); }

  constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
  constexpr const_iterator cend() const noexcept { return container_.cend(); }
  constexpr const_reverse_iterator crbegin() const noexcept { return container_.crbegin(); }
  constexpr const_reverse_iterator crend() const noexcept { return container_.crend(); }

  // Reduce ----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class BinaryOperation>
  [[nodiscard]] constexpr value_type
  reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) && {
    return std::reduce(std::forward<ExecutionPolicy>(policy),
                       std::make_move_iterator(container_.begin()),
                       std::make_move_iterator(container_.end()),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }
  template <class ExecutionPolicy, class BinaryOperation>
  [[nodiscard]] constexpr value_type
  reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) const& {
    return std::reduce(std::forward<ExecutionPolicy>(policy),
                       container_.begin(),
                       container_.end(),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }

  template <class BinaryOperation>
  [[nodiscard]] constexpr value_type reduce(BinaryOperation&& op, value_type init) && {
    return std::reduce(std::make_move_iterator(container_.begin()),
                       std::make_move_iterator(container_.end()),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }
  template <class BinaryOperation>
  [[nodiscard]] constexpr value_type reduce(BinaryOperation&& op, value_type init) const& {
    return std::reduce(container_.begin(),
                       container_.end(),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }

  // Transform -------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class UnaryOperation>
  [[nodiscard]] constexpr auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) && {
    using result_type = std::invoke_result_t<UnaryOperation, value_type>;

    if constexpr (std::is_same_v<result_type, value_type>) {
      std::for_each(std::forward<ExecutionPolicy>(policy),
                    container_.begin(),
                    container_.end(),
                    [map_value = std::forward<UnaryOperation>(op)](value_type& value) {
                      value = std::move(map_value(value));
                    });

      return std::move(*this);
    } else {
      collection_internal::ResultCollection<container_type, result_type> result;

      std::transform(std::forward<ExecutionPolicy>(policy),
                     std::make_move_iterator(container_.begin()),
                     std::make_move_iterator(container_.end()),
                     result.begin(),
                     std::forward<UnaryOperation>(op));

      return result;
    }
  }
  template <class ExecutionPolicy, class UnaryOperation>
  [[nodiscard]] constexpr auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) const& {
    return Collection(*this).transform(std::forward<ExecutionPolicy>(policy),
                                       std::forward<UnaryOperation>(op));
  }

  template <class UnaryOperation>
  [[nodiscard]] constexpr auto transform(UnaryOperation&& op) && {
    using result_type = std::invoke_result_t<UnaryOperation, value_type>;

    if constexpr (std::is_same_v<result_type, value_type>) {
      auto&& map_value = std::forward<UnaryOperation>(op);
      for (value_type& value : container_) {
        value = std::move(map_value(value));
      }
      return std::move(*this);
    } else {
      collection_internal::ResultCollection<container_type, result_type> result;

      std::transform(std::make_move_iterator(container_.begin()),
                     std::make_move_iterator(container_.end()),
                     result.begin(),
                     std::forward<UnaryOperation>(op));

      return result;
    }
  }
  template <class UnaryOperation>
  [[nodiscard]] constexpr auto transform(UnaryOperation&& op) const& {
    return Collection(*this).transform(std::forward<UnaryOperation>(op));
  }

  // Dynamicize ------------------------------------------------------------------------------------
  template <template <class...> class C = std::vector>
  constexpr auto dynamicize() const& { // NOLINT(*-naming*)
    return Collection<value_type, C<value_type>>(container_.begin(), container_.end());
  }

  template <template <class...> class C = std::vector>
  constexpr auto dynamicize() && { // NOLINT(*-naming*)
    return Collection<value_type, C<value_type>>(std::make_move_iterator(container_.begin()),
                                                 std::make_move_iterator(container_.end()));
  }

  template <class C>
  constexpr auto dynamicize() const& { // NOLINT(*-naming*)
    return Collection<value_type, C>(container_.begin(), container_.end());
  }

  template <class C>
  constexpr auto dynamicize() && { // NOLINT(*-naming*)
    return Collection<value_type, C>(std::make_move_iterator(container_.begin()),
                                     std::make_move_iterator(container_.end()));
  }

  // Sorts -----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class Cmp>
  constexpr void sort(ExecutionPolicy&& policy, Cmp cmp) & {
    std::sort(std::forward<ExecutionPolicy>(policy), container_.begin(), container_.end(), cmp);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection sorted(ExecutionPolicy&& policy, Cmp cmp) && {
    return sort(std::forward<ExecutionPolicy>(policy), cmp), std::move(*this);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection sorted(ExecutionPolicy&& policy, Cmp cmp) const& {
    return Collection(*this).sorted(std::forward<ExecutionPolicy>(policy), cmp);
  }

  template <class Cmp = std::ranges::less>
  constexpr void sort(Cmp cmp = {}) & {
    std::ranges::sort(container_, cmp);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection sorted(Cmp cmp = {}) && {
    return sort(cmp), std::move(*this);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection sorted(Cmp cmp = {}) const& {
    return Collection(*this).sorted(cmp);
  }

  // NOLINTBEGIN(*-naming*)
  template <class ExecutionPolicy, class Cmp>
  constexpr void stable_sort(ExecutionPolicy&& policy, Cmp cmp) & {
    std::stable_sort(std::forward<ExecutionPolicy>(policy),
                     container_.begin(),
                     container_.end(),
                     cmp);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection stable_sorted(ExecutionPolicy&& policy, Cmp cmp) && {
    return stable_sort(std::forward<ExecutionPolicy>(policy), cmp), std::move(*this);
  }
  template <class ExecutionPolicy, class Cmp>
  [[nodiscard]] constexpr Collection stable_sorted(ExecutionPolicy&& policy, Cmp cmp) const& {
    return Collection(*this).stable_sorted(std::forward<ExecutionPolicy>(policy), cmp);
  }

  template <class Cmp = std::ranges::less>
  constexpr void stable_sort(Cmp cmp = {}) & {
    std::ranges::stable_sort(container_, cmp);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection stable_sorted(Cmp cmp = {}) && {
    return stable_sort(cmp), std::move(*this);
  }
  template <class Cmp = std::ranges::less>
  [[nodiscard]] constexpr Collection stable_sorted(Cmp cmp = {}) const& {
    return Collection(*this).stable_sorted(cmp);
  }
  // NOLINTEND(*-naming*)

  // Reverse ---------------------------------------------------------------------------------------
  template <class ExecutionPolicy>
  constexpr void reverse(ExecutionPolicy&& policy) & {
    std::reverse(std::forward<ExecutionPolicy>(policy), container_.begin(), container_.end());
  }
  template <class ExecutionPolicy>
  [[nodiscard]] constexpr Collection reversed(ExecutionPolicy&& policy) && {
    return reverse(std::forward<ExecutionPolicy>(policy)), std::move(*this);
  }
  template <class ExecutionPolicy>
  [[nodiscard]] constexpr Collection reversed(ExecutionPolicy&& policy) const& {
    return Collection(*this).reversed(std::forward<ExecutionPolicy>(policy));
  }

  constexpr void reverse() & { std::ranges::reverse(container_); }
  [[nodiscard]] constexpr Collection reversed() && { return reverse(), std::move(*this); }
  [[nodiscard]] constexpr Collection reversed() const& { return Collection(*this).reversed(); }

  // Contains --------------------------------------------------------------------------------------
  template <class ExecutionPolicy>
  constexpr bool contains(ExecutionPolicy&& policy, const value_type& value) const {
    return std::find(std::forward<ExecutionPolicy>(policy),
                     container_.begin(),
                     container_.end(),
                     value)
           != container_.end();
  }

  template <class ExecutionPolicy, class U>
  constexpr bool contains(ExecutionPolicy&& policy, const U& value) const {
    return std::find(std::forward<ExecutionPolicy>(policy),
                     container_.begin(),
                     container_.end(),
                     value)
           != container_.end();
  }

  constexpr bool contains(const value_type& value) const {
    return std::ranges::find(container_, value) != container_.end();
  }

  template <class U>
  constexpr bool contains(const U& value) const {
    return std::ranges::find(container_, value) != container_.end();
  }

  // Implicit conversions --------------------------------------------------------------------------
  constexpr explicit operator bool() const noexcept { return not container_.empty(); }

  constexpr operator container_type() const& { return container_; }        // NOLINT(*-explicit*)
  constexpr operator container_type() && { return std::move(container_); } // NOLINT(*-explicit*)

  template <std::ranges::range R>
  constexpr operator R() const& { // NOLINT(*-explicit*)
    return R(container_.begin(), container_.end());
  }
  template <std::ranges::range R>
  constexpr operator R() && { // NOLINT(*-explicit*)
    return R(std::make_move_iterator(container_.begin()),
             std::make_move_iterator(container_.end()));
  }

  template <class F, class S>
  constexpr operator std::pair<F, S>() const& { // NOLINT(*-explicit*)
    value_type first{};
    value_type second{};
    if (const_iterator it = container_.begin(); it != container_.end()) {
      first = *it;
      if (++it != end()) {
        second = *it;
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }
  template <class F, class S>
  constexpr operator std::pair<F, S>() && { // NOLINT(*-explicit*)
    value_type first{};
    value_type second{};
    if (iterator it = container_.begin(); it != container_.end()) {
      first = std::move(*it);
      if (++it != end()) {
        second = std::move(*it);
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }

  template <class... Ts>
  constexpr operator std::tuple<Ts...>() const& { // NOLINT(*-explicit*)
    std::tuple<Ts...> result{};
    collection_internal::assign(result, *this);
    return result;
  }
  template <class... Ts>
  constexpr operator std::tuple<Ts...>() && { // NOLINT(*-explicit*)
    std::tuple<Ts...> result{};
    collection_internal::assign(result, std::move(*this));
    return result;
  }

 private:
  container_type container_;
};

// Aliases -----------------------------------------------------------------------------------------
template <class T, std::size_t N>
using ArrayCollection = Collection<T, std::array<T, N>>;

// Make functions ----------------------------------------------------------------------------------
template <class T, class... Args>
constexpr ArrayCollection<T, sizeof...(Args)> make_collection(Args&&... args) { // NOLINT(*-naming*)
  return {std::forward<Args>(args)...};
}

template <class... Args>
constexpr ArrayCollection<std::common_type_t<std::remove_cvref_t<Args>...>, sizeof...(Args)>
make_collection(Args&&... args) { // NOLINT(*-naming*)
  return {std::forward<Args>(args)...};
}

template <class T, class... Args>
constexpr Collection<T> make_dynamic_collection(Args&&... args) { // NOLINT(*-naming*)
  Collection<T> result;
  result.reserve(sizeof...(Args));
  return (result.emplace_back(std::forward<Args>(args)), ...), result;
}

template <class... Args>
constexpr Collection<std::common_type_t<std::remove_cvref_t<Args>...>>
make_dynamic_collection(Args&&... args) { // NOLINT(*-naming*)
  Collection<std::common_type_t<std::remove_cvref_t<Args>...>> result;
  result.reserve(sizeof...(Args));
  return (result.emplace_back(std::forward<Args>(args)), ...), result;
}

// Deduction guides --------------------------------------------------------------------------------
template <class T, std::size_t N>
Collection(T (&)[N]) -> Collection<T, std::array<T, N>>; // NOLINT(*-avoid-c-arrays)

template <class T, std::size_t N>
Collection(const T (&)[N]) -> Collection<T, std::array<T, N>>; // NOLINT(*-avoid-c-arrays)

template <class T, std::size_t N>
Collection(T (&&)[N]) -> Collection<T, std::array<T, N>>; // NOLINT(*-avoid-c-arrays)

template <class T, std::size_t N>
Collection(const T (&&)[N]) -> Collection<T, std::array<T, N>>; // NOLINT(*-avoid-c-arrays)

template <class T, std::size_t N>
Collection(std::array<T, N>&) -> Collection<T, std::array<T, N>>;

template <class T, std::size_t N>
Collection(const std::array<T, N>&) -> Collection<T, std::array<T, N>>;

template <class T, std::size_t N>
Collection(std::array<T, N>&&) -> Collection<T, std::array<T, N>>;

template <class T, std::size_t N>
Collection(const std::array<T, N>&&) -> Collection<T, std::array<T, N>>;

template <class T>
Collection(std::initializer_list<T>) -> Collection<T>;

template <class T>
Collection(const std::vector<T>&) -> Collection<T, std::vector<T>>;

template <class T>
Collection(std::vector<T>&&) -> Collection<T, std::vector<T>>;

template <std::ranges::range R>
Collection(R&&) -> Collection<std::remove_reference_t<std::ranges::range_reference_t<R>>>;

} // namespace robocin

// Standard library specializations ----------------------------------------------------------------

// NOLINTBEGIN(*-dcl58-cpp, *-rvalue*)
namespace std {

template <class T, class Container>
constexpr void swap(::robocin::Collection<T, Container>& lhs,
                    ::robocin::Collection<T, Container>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

template <size_t I, class T, size_t N>
  requires(I < N)
constexpr T& get(::robocin::Collection<T, array<T, N>>& collection) noexcept {
  return collection[I];
}

template <size_t I, class T, size_t N>
  requires(I < N)
constexpr const T& get(const ::robocin::Collection<T, array<T, N>>& collection) noexcept {
  return collection[I];
}

template <size_t I, class T, size_t N>
  requires(I < N)
constexpr T&& get(::robocin::Collection<T, array<T, N>>&& collection) noexcept {
  return move(collection[I]);
}

template <size_t I, class T, size_t N>
  requires(I < N)
constexpr const T&& get(const ::robocin::Collection<T, array<T, N>>&& collection) noexcept {
  return move(collection[I]);
}

template <class T, size_t N>
struct tuple_size<::robocin::Collection<T, array<T, N>>> : integral_constant<size_t, N> {};

template <size_t I, class T, size_t N>
struct tuple_element<I, ::robocin::Collection<T, array<T, N>>> {
  using type = T;
};

} // namespace std
// NOLINTEND(*-dcl58-cpp, *-rvalue*)

#endif // ROBOCIN_COLLECTION_COLLECTION_H
