//
// Created by José Cruz <joseviccruz> on 27/03/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_UTILITY_COLLECTION_H
#define ROBOCIN_UTILITY_COLLECTION_H

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

  // NOLINTBEGIN(cppcoreguidelines-c-copy-assignment-signature)
  // NOLINTBEGIN(misc-unconventional-assign-operator)
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
  // NOLINTEND(misc-unconventional-assign-operator)
  // NOLINTEND(cppcoreguidelines-c-copy-assignment-signature)

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
  constexpr size_type max_size() // NOLINT(readability-identifier-naming)
      const {
    return container_.max_size();
  }
  constexpr void reserve(size_type new_cap) { container_.reserve(new_cap); }
  constexpr size_type capacity() const { return container_.capacity(); }
  constexpr void shrink_to_fit() // NOLINT(readability-identifier-naming)
  {
    container_.shrink_to_fit();
  }

  // Modifiers -------------------------------------------------------------------------------------
  // NOLINTBEGIN(readability-identifier-naming)
  constexpr void append_range(const Collection& other) {
    container_.insert(container_.end(), other.container_.begin(), other.container_.end());
  }
  constexpr void append_range(Collection&& other) {
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
  // NOLINTEND(readability-identifier-naming)

  constexpr void clear() { container_.clear(); }

  template <class... Args>
  constexpr iterator emplace(Args&&... args) {
    return container_.emplace(std::forward<Args>(args)...);
  }

  template <class... Args>
  constexpr reference emplace_back(Args&&... args) { // NOLINT(readability-identifier-naming)
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

  constexpr void push_back(const value_type& value) // NOLINT(readability-identifier-naming)
  {
    container_.push_back(value);
  }
  constexpr void push_back(value_type&& value) // NOLINT(readability-identifier-naming)
  {
    container_.push_back(std::move(value));
  }

  constexpr void pop_back() { container_.pop_back(); } // NOLINT(readability-identifier-naming)

  constexpr void resize(size_type count) { container_.resize(count); }
  constexpr void resize(size_type count, const value_type& value) {
    container_.resize(count, value);
  }

  constexpr void swap(Collection& other) { std::swap(container_, other.container_); }

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

  // Filter ----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class UnaryPredicate>
  Collection filter(ExecutionPolicy&& policy, UnaryPredicate&& predicate) && {
    iterator last = std::remove_if(std::forward<ExecutionPolicy>(policy),
                                   container_.begin(),
                                   container_.end(),
                                   std::not_fn(std::forward<UnaryPredicate>(predicate)));

    container_.erase(last, container_.end());
    return std::move(*this);
  }

  template <class ExecutionPolicy, class UnaryPredicate>
  Collection filter(ExecutionPolicy&& policy, UnaryPredicate&& predicate) const& {
    return Collection(*this).filter(std::forward<ExecutionPolicy>(policy),
                                    std::forward<UnaryPredicate>(predicate));
  }

  template <class UnaryPredicate>
  Collection filter(UnaryPredicate&& predicate) && {
    iterator last = std::remove_if(container_.begin(),
                                   container_.end(),
                                   std::not_fn(std::forward<UnaryPredicate>(predicate)));

    container_.erase(last, container_.end());
    return std::move(*this);
  }

  template <class UnaryPredicate>
  Collection filter(UnaryPredicate&& predicate) const& {
    return Collection(*this).filter(std::forward<UnaryPredicate>(predicate));
  }

  // Reduce ----------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class BinaryOperation>
  value_type reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) && {
    return std::reduce(std::forward<ExecutionPolicy>(policy),
                       container_.begin(),
                       container_.end(),
                       std::move(init),
                       std::forward<BinaryOperation>(op));
  }

  template <class ExecutionPolicy, class BinaryOperation>
  value_type reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) const& {
    return Collection(*this).reduce(std::forward<ExecutionPolicy>(policy),
                                    std::forward<BinaryOperation>(op),
                                    std::move(init));
  }

  template <class BinaryOperation>
  value_type reduce(BinaryOperation&& op, value_type init) && {
    return std::move(*this).reduce(std::execution::seq,
                                   std::forward<BinaryOperation>(op),
                                   std::move(init));
  }

  template <class BinaryOperation>
  value_type reduce(BinaryOperation&& op, value_type init) const& {
    return Collection(*this).reduce(std::execution::seq,
                                    std::forward<BinaryOperation>(op),
                                    std::move(init));
  }

  // Transform -------------------------------------------------------------------------------------
  template <class ExecutionPolicy, class UnaryOperation>
  auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) && {
    using result_type = std::invoke_result_t<UnaryOperation, value_type>;

    Collection<result_type> result(container_.size());

    std::transform(std::forward<ExecutionPolicy>(policy),
                   container_.begin(),
                   container_.end(),
                   result.begin(),
                   std::forward<UnaryOperation>(op));

    return result;
  }

  template <class ExecutionPolicy, class UnaryOperation>
  auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) const& {
    return Collection(*this).transform(std::forward<ExecutionPolicy>(policy),
                                       std::forward<UnaryOperation>(op));
  }

  template <class UnaryOperation>
  auto transform(UnaryOperation&& op) && {
    using result_type = std::invoke_result_t<UnaryOperation, value_type>;

    Collection<result_type> result;
    result.reserve(container_.size());

    std::transform(container_.begin(),
                   container_.end(),
                   std::back_inserter(result.container_),
                   std::forward<UnaryOperation>(op));

    return result;
  }

  template <class UnaryOperation>
  auto transform(UnaryOperation&& op) const& {
    return Collection(*this).transform(std::forward<UnaryOperation>(op));
  }

  // Flat transform --------------------------------------------------------------------------------
  // NOLINTBEGIN(readability-identifier-naming)
  template <class ExecutionPolicy, class UnaryOperation>
    requires(std::ranges::range<value_type>)
  auto flat_transform(ExecutionPolicy&& policy, UnaryOperation&& op) && {
    using input_type = std::ranges::range_value_t<value_type>;
    using result_type = std::invoke_result_t<UnaryOperation, input_type>;

    size_t result_size = std::accumulate(container_.begin(),
                                         container_.end(),
                                         size_t{0},
                                         [](size_t acc, const value_type& range) {
                                           return acc + range.size();
                                         });
    Collection<result_type> result(result_size);

    auto&& pol = std::forward<ExecutionPolicy>(policy);
    auto&& fun = std::forward<UnaryOperation>(op);
    auto&& out = result.begin();

    for (auto&& element : container_) {
      out = std::transform(pol, std::begin(element), std::end(element), out, fun);
    }

    return result;
  }

  template <class ExecutionPolicy, class UnaryOperation>
    requires(std::ranges::range<value_type>)
  auto flat_transform(ExecutionPolicy&& policy, UnaryOperation&& op) const& {
    return Collection(*this).flat_transform(std::forward<ExecutionPolicy>(policy),
                                            std::forward<UnaryOperation>(op));
  }

  template <class UnaryOperation>
    requires(std::ranges::range<value_type>)
  auto flat_transform(UnaryOperation&& op) && {
    using input_type = std::ranges::range_value_t<value_type>;
    using result_type = std::invoke_result_t<UnaryOperation, input_type>;

    Collection<result_type> result;
    size_t result_size = std::accumulate(container_.begin(),
                                         container_.end(),
                                         size_t{0},
                                         [](size_t acc, const value_type& range) {
                                           return acc + range.size();
                                         });
    result.reserve(result_size);

    auto&& fun = std::forward<UnaryOperation>(op);
    for (auto&& element : container_) {
      auto&& transformed = std::views::transform(element, fun);
      result.insert(result.end(), std::begin(transformed), std::end(transformed));
    }

    return result;
  }

  template <class UnaryOperation>
    requires(std::ranges::range<value_type>)
  auto flat_transform(UnaryOperation&& op) const& {
    return Collection(*this).flat_transform(std::forward<UnaryOperation>(op));
  }
  // NOLINTEND(readability-identifier-naming)

  // Implicit conversions --------------------------------------------------------------------------
  constexpr explicit operator bool() const noexcept { return !container_.empty(); }

  constexpr
  operator container_type() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      const& {
    return container_;
  }
  constexpr
  operator container_type() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      && {
    return std::move(container_);
  }

  template <std::ranges::range R>
  constexpr operator R() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      const& {
    return R(container_.begin(), container_.end());
  }
  template <std::ranges::range R>
  constexpr operator R() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      && {
    return R(std::make_move_iterator(container_.begin()),
             std::make_move_iterator(container_.end()));
  }

  template <class F, class S>
  constexpr
  operator std::pair<F, S>() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      const& {
    value_type first{};
    value_type second{};
    if (const_iterator it = begin(); it != end()) {
      first = *it;
      if (++it != end()) {
        second = *it;
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }
  template <class F, class S>
  constexpr
  operator std::pair<F, S>() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      && {
    value_type first{};
    value_type second{};
    if (iterator it = begin(); it != end()) {
      first = std::move(*it);
      if (++it != end()) {
        second = std::move(*it);
      }
    }
    return {F(std::move(first)), S(std::move(second))};
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

  // Comparison operators --------------------------------------------------------------------------
  inline constexpr bool operator==(const Collection& other) const {
    return container_ == other.container_;
  }
  inline constexpr auto operator<=>(const Collection& other) const {
    return container_ <=> other.container_;
  }

  // Transform -------------------------------------------------------------------------------------
  template <template <class...> class C = std::vector>
  constexpr auto transform_dynamic() const& { // NOLINT(readability-identifier-naming)
    return Collection<value_type, C<value_type>>(container_.begin(), container_.end());
  }

  template <template <class...> class C = std::vector>
  constexpr auto transform_dynamic() && { // NOLINT(readability-identifier-naming)
    return Collection<value_type, C<value_type>>(std::make_move_iterator(container_.begin()),
                                                 std::make_move_iterator(container_.end()));
  }

  template <class C>
  constexpr auto transform_dynamic() const& { // NOLINT(readability-identifier-naming)
    return Collection<value_type, C>(container_.begin(), container_.end());
  }

  template <class C>
  constexpr auto transform_dynamic() && { // NOLINT(readability-identifier-naming)
    return Collection<value_type, C>(std::make_move_iterator(container_.begin()),
                                     std::make_move_iterator(container_.end()));
  }

  // Implicit conversions --------------------------------------------------------------------------
  constexpr explicit operator bool() const noexcept { return !container_.empty(); }

  constexpr
  operator container_type() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      const& {
    return container_;
  }
  constexpr
  operator container_type() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      && {
    return std::move(container_);
  }

  template <std::ranges::range R>
  constexpr operator R() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      const& {
    return R(container_.begin(), container_.end());
  }
  template <std::ranges::range R>
  constexpr operator R() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      && {
    return R(std::make_move_iterator(container_.begin()),
             std::make_move_iterator(container_.end()));
  }

  template <class F, class S>
  constexpr
  operator std::pair<F, S>() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      const& {
    value_type first{};
    value_type second{};
    if (const_iterator it = begin(); it != end()) {
      first = *it;
      if (++it != end()) {
        second = *it;
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }
  template <class F, class S>
  constexpr
  operator std::pair<F, S>() // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
      && {
    value_type first{};
    value_type second{};
    if (iterator it = begin(); it != end()) {
      first = std::move(*it);
      if (++it != end()) {
        second = std::move(*it);
      }
    }
    return {F(std::move(first)), S(std::move(second))};
  }

 private:
  container_type container_;
};

template <class T, std::size_t N>
using ArrayCollection = Collection<T, std::array<T, N>>;

// Deduction guides --------------------------------------------------------------------------------
template <class T, std::size_t N>
Collection(T (&)[N]) // NOLINT(*-avoid-c-arrays)
    ->Collection<T, std::array<T, N>>;

template <class T, std::size_t N>
Collection(const T (&)[N]) // NOLINT(*-avoid-c-arrays)
    ->Collection<T, std::array<T, N>>;

template <class T, std::size_t N>
Collection(T (&&)[N]) // NOLINT(*-avoid-c-arrays)
    ->Collection<T, std::array<T, N>>;

template <class T, std::size_t N>
Collection(const T (&&)[N]) // NOLINT(*-avoid-c-arrays)
    ->Collection<T, std::array<T, N>>;

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

template <class R>
Collection(R&&) -> Collection<std::remove_reference_t<std::ranges::range_reference_t<R>>>;

} // namespace robocin

#endif // ROBOCIN_UTILITY_COLLECTION_H
