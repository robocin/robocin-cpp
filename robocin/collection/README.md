# Collection

## Overview

The `Collection` class is a versatile container adaptor designed to provide the programmer with an extended interface
for handling sequences of elements, resembling the functionalities of both static and dynamic size arrays. It serves as
a powerful alternative to the standard `std::vector` and `std::array` containers, enhancing their capabilities with
additional map/reduce-like methods and several other utilities.

### Key Features

* **Versatility**: The Collection class can accommodate both static-size and dynamic-size collections, making it
  adaptable to different use cases. Whether you need a fixed-size collection or one that can grow or shrink as needed,
  the Collection class has you covered.

* **Map/Reduce-like Methods**: The class offers map, reduce, filter, and transform methods, inspired by functional
  programming paradigms. These methods allow you to perform element-wise operations, aggregate results, and selectively
  filter elements based on conditions with ease and readability.

* **Efficient Parallel Operations**: Certain methods, such as `stable_sort` and `reverse`, support parallel execution
  using the provided execution policies. This feature leverages modern hardware capabilities, such as multi-core
  processors, to perform computations faster on large datasets.

* **Sorting and Reversing**: The Collection class provides various sorting algorithms, including both stable and
  non-stable sorts, allowing you to organize the elements according to specific criteria. Additionally, you can easily
  reverse the order of elements with a single function call.

* **Implicit Conversions**: The class supports implicit conversions to other data structures, such as standard
  containers like `std::vector`, ranges, pairs, and tuples. This convenient feature simplifies interoperability with
  existing codebases and enables easy integration with other standard library components.

## Aliases

- `template <class T, std::size_t N> using ArrayCollection = Collection<T, std::array<T, N>>`: The `ArrayCollection`
  alias creates a new template specialization of the Collection class that uses std::array as its underlying container
  type. This alias allows users to work with static-size arrays using the familiar Collection interface.

## Member Types

- `container_type`: The type of the underlying container used to store elements.
- `value_type`: The type of the elements held in the collection.
- `size_type`: An unsigned integral type used for representing sizes and indices.
- `reference`: A reference type to the elements in the container.
- `const_reference`: A const reference type to the elements in the container.
- `iterator`: An iterator type to traverse the collection.
- `const_iterator`: A const iterator type to traverse the collection.
- `reverse_iterator`: A reverse iterator type to traverse the collection in reverse.
- `const_reverse_iterator`: A const reverse iterator type to traverse the collection in reverse.

## Constructors

- `Collection()`: Default constructor, constructs an empty collection.
- `Collection(const Collection& other)`: Copy constructor, creates a new collection by copying elements from another
  collection.
- `Collection(Collection&& other) noexcept`: Move constructor, creates a new collection by moving elements from another
  collection.
- `explicit Collection(size_type count)`: Constructs the collection with `count` default-inserted instances
  of `value_type`.
- `Collection(size_type count, const value_type& value)`: Constructs the collection with `count` copies of `value`.
- `Collection(std::initializer_list<value_type> il)`: Constructs the collection with the elements from the initializer
  list `il`.
- `explicit Collection(const container_type& container)`: Constructs the collection by copying the elements from the
  provided `container`.
- `explicit Collection(container_type&& container)`: Constructs the collection by moving the elements from the
  provided `container`.
- `template <class FirstIt, class LastIt> Collection(FirstIt first, LastIt last)`: Constructs the collection with
  elements in the range `[first, last)`.
- `template <std::ranges::range R> explicit Collection(R&& range)`: Constructs the collection with elements from the
  range `range`.

## Assignment Operators

- `Collection& operator=(const Collection& other)`: Copy assignment operator, assigns the elements from another
  collection to this collection.
- `Collection& operator=(Collection&& other) noexcept`: Move assignment operator, moves the elements from another
  collection to this collection.
- `Collection& operator=(std::initializer_list<value_type> il)`: Assigns the elements from the initializer list `il` to
  the collection.
- `Collection& operator=(const container_type& container)`: Assigns the elements from the provided `container` to this
  collection by copying them.
- `Collection& operator=(container_type&& container)`: Assigns the elements from the provided `container` to this
  collection by moving them.
- `template <std::ranges::range R> Collection& operator=(R&& range)`: Assigns the elements from the range `range` to
  the collection.

## Element Access

- `reference at(size_type pos)`: Returns a reference to the element at the specified position `pos` with bounds
  checking.
- `const_reference at(size_type pos) const`: Returns a const reference to the element at the specified position `pos`
  with bounds checking.
- `reference operator[](size_type pos)`: Returns a reference to the element at the specified position `pos`. No bounds
  checking is performed.
- `const_reference operator[](size_type pos) const`: Returns a const reference to the element at the specified
  position `pos`. No bounds checking is performed.
- `reference front()`: Returns a reference to the first element in the collection.
- `const_reference front() const`: Returns a const reference to the first element in the collection.
- `reference back()`: Returns a reference to the last element in the collection.
- `const_reference back() const`: Returns a const reference to the last element in the collection.

## Capacity

- `bool empty() const`: Returns a boolean indicating whether the collection is empty (i.e., contains no elements).
- `size_type size() const`: Returns the number of elements currently stored in the collection.
- `size_type max_size() const`: Returns the maximum possible number of elements the collection can hold. The actual
  limit may vary depending on the system and memory constraints.
- `void reserve(size_type new_cap)`: Requests that the collection's underlying container reserve memory for at
  least `new_cap` elements. This can help to reduce reallocations during insertions and prevent unnecessary memory
  reallocation.
- `size_type capacity() const`: Returns the current capacity of the collection, which is the maximum number
  of elements it can hold without triggering a reallocation.
- `void shrink_to_fit()`: Requests the collection's underlying container to deallocate any unused memory
  beyond the current size. This operation may or may not result in a reallocation.

## Modifiers

> **Note**: The following modifiers are not available for collections that use `std::array` as their underlying
> container type.

- `void append_range(const Collection& other)`: Appends the elements from another collection `other` at the
  end of this collection.
- `void append_range(Collection&& other)`: Appends the elements from another collection `other` at the end of
  this collection, using move semantics when applicable. Note that the original `other` collection is not modified.
- `void append_range(std::initializer_list<value_type> il)`: Appends elements from the initializer list `il`
  at the end of this collection.
- `template <std::ranges::range R> void append_range(R&& range)`: Appends elements from the range `range` at
  the end of this collection.

- `void clear()`: Removes all elements from the collection, leaving it with a size of 0.

- `template <class... Args> iterator emplace(Args&&... args)`: Constructs an element in-place at the given
  position using the provided arguments `args`.

- `template <class... Args> reference emplace_back(Args&&... args)`: Constructs an element in-place at the
  end of the collection using the provided arguments `args` and returns a reference to the newly constructed element.

- `void erase(const_iterator pos)`: Removes the element at the specified position `pos`.

- `void erase(const_iterator first, const_iterator last)`: Removes elements in the range `[first, last)` from
  the collection.

- `iterator insert(const_iterator pos, const value_type& value)`: Inserts a copy of `value` before the
  specified position `pos` and returns an iterator pointing to the inserted element.

- `iterator insert(const_iterator pos, value_type&& value)`: Inserts a moved element `value` before the
  specified position `pos` and returns an iterator pointing to the inserted element.

- `iterator insert(const_iterator pos, size_type count, const value_type& value)`: Inserts `count` copies
  of `value` before the specified position `pos` and returns an iterator pointing to the first inserted element.

- `template <class FirstIt, class LastIt> iterator insert(const_iterator pos, FirstIt first, LastIt last)`:
  Inserts elements from the range `[first, last)` before the specified position `pos` and returns an iterator pointing
  to the first inserted element.

- `iterator insert(const_iterator pos, std::initializer_list<value_type> il)`: Inserts elements from the
  initializer list `il` before the specified position `pos` and returns an iterator pointing to the first inserted
  element.

- `template <std::ranges::range R> iterator insert(const_iterator pos, R&& range)`: Inserts elements from
  the range `range` before the specified position `pos` and returns an iterator pointing to the first inserted
  element.

- `void push_back(const value_type& value)`: Appends a copy of `value` to the end of the collection.

- `void push_back(value_type&& value)`: Appends a moved element `value` to the end of the collection.

- `void pop_back()`: Removes the last element of the collection.

- `void resize(size_type count)`: Resizes the collection to contain `count` elements. If `count` is smaller
  than the current size, elements are removed from the end. If `count` is greater, additional default-constructed
  elements are appended.

- `void resize(size_type count, const value_type& value)`: Resizes the collection to contain `count`
  elements. If `count` is smaller than the current size, elements are removed from the end. If `count` is greater,
  additional copies of `value` are appended.

- `Collection resized(size_type count) &&`: Resizes the collection to contain `count` elements and returns a
  reference to the resized collection using move semantics. If `count` is smaller than the current size, elements are
  removed from the end. If `count` is greater, additional default-constructed elements are appended.

- `Collection resized(size_type count) const&`: Creates a copy of the collection, resizes it to
  contain `count` elements, and returns the resized copy. If `count` is smaller than the current size, elements are
  removed from the end. If `count` is greater, additional default-constructed elements are appended.

- `Collection resized(size_type count, const value_type& value) &&`: Resizes the collection to
  contain `count` elements, setting each new element to `value`, and returns a reference to the resized collection
  using move semantics. If `count` is smaller than the current size, elements are removed from the end. If `count` is
  greater, additional copies of `value` are appended.

- `Collection resized(size_type count, const value_type& value) const&`: Creates a copy of the collection,
  resizes it to contain `count` elements, setting each new element to `value`, and returns the resized copy.
  If `count` is smaller than the current size, elements are removed from the end. If `count` is greater, additional
  copies of `value` are appended.

- `void swap(Collection& other)`: Swaps the contents of this collection with another collection `other`.

## Comparison Operators

- `inline bool operator==(const Collection& other) const`: Compares this collection with another
  collection `other` for equality. Returns `true` if both collections have the same elements in the same order;
  otherwise, returns `false`.

- `inline auto operator<=>(const Collection& other) const`: Compares this collection with another
  collection `other`. Returns a three-way comparison result indicating whether this collection is less than, equal to,
  or greater than `other`.

## Iterators

- `iterator begin() noexcept`: Returns an iterator pointing to the first element of the collection.
- `const_iterator begin() const noexcept`: Returns a constant iterator pointing to the first element of the
  collection.
- `iterator end() noexcept`: Returns an iterator pointing to the element following the last element of the
  collection.
- `const_iterator end() const noexcept`: Returns a constant iterator pointing to the element following the
  last element of the collection.

- `reverse_iterator rbegin() noexcept`: Returns a reverse iterator pointing to the last element of the
  collection (reverse beginning).
- `const_reverse_iterator rbegin() const noexcept`: Returns a constant reverse iterator pointing to the last
  element of the collection (reverse beginning).
- `reverse_iterator rend() noexcept`: Returns a reverse iterator pointing to the element preceding the first
  element of the collection (reverse end).
- `const_reverse_iterator rend() const noexcept`: Returns a constant reverse iterator pointing to the element
  preceding the first element of the collection (reverse end).

- `const_iterator cbegin() const noexcept`: Returns a constant iterator pointing to the first element of the
  collection. Similar to `begin()`.
- `const_iterator cend() const noexcept`: Returns a constant iterator pointing to the element following the
  last element of the collection. Similar to `end()`.
- `const_reverse_iterator crbegin() const noexcept`: Returns a constant reverse iterator pointing to the
  last element of the collection (reverse beginning). Similar to `rbegin()`.
- `const_reverse_iterator crend() const noexcept`: Returns a constant reverse iterator pointing to the
  element preceding the first element of the collection (reverse end). Similar to `rend()`.

## Reduce

- `template <class ExecutionPolicy, class BinaryOperation> value_type reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) &&`:
  Reduces the elements in the collection using the provided binary operation `op` and an initial value `init`. The
  reduction is performed using the specified execution policy `policy`. The collection is modified using
  move semantics during the reduction process.

- `template <class ExecutionPolicy, class BinaryOperation> value_type reduce(ExecutionPolicy&& policy, BinaryOperation&& op, value_type init) const&`:
  Reduces the elements in the collection using the provided binary operation `op` and an initial value `init`. The
  reduction is performed using the specified execution policy `policy`. A copy of the collection is made
  for the reduction process to keep the original collection unchanged.

- `template <class BinaryOperation> value_type reduce(BinaryOperation&& op, value_type init) &&`:
  Reduces the elements in the collection using the provided binary operation `op` and an initial value `init`. The
  collection is modified using move semantics during the reduction process. The reduction is performed sequentially.

- `template <class BinaryOperation> value_type reduce(BinaryOperation&& op, value_type init) const&`:
  Reduces the elements in the collection using the provided binary operation `op` and an initial value `init`. A copy
  of the collection is made for the reduction process to keep the original collection unchanged. The reduction is
  performed sequentially.

## Filter

> **Note**: The following filtering methods are not available for collections that use `std::array` as the underlying
> container type.

- `template <class ExecutionPolicy, class UnaryPredicate> void filter(ExecutionPolicy&& policy, UnaryPredicate&& predicate) &`:
  Modifies the collection, removing elements for which the unary predicate `predicate` returns false. The filtering is
  performed using the specified execution policy `policy`.

- `template <class ExecutionPolicy, class UnaryPredicate> Collection filtered(ExecutionPolicy&& policy, UnaryPredicate&& predicate) &&`:
  Modifies the collection and returns a reference to the modified collection using move semantics, removing elements
  for which the unary predicate `predicate` returns false. The filtering is performed using the specified execution
  policy `policy`.

- `template <class ExecutionPolicy, class UnaryPredicate> Collection filtered(ExecutionPolicy&& policy, UnaryPredicate&& predicate) const&`:
  Creates a copy of the collection and applies filtering to the copy. The original collection is unchanged. The
  filtering is performed using the specified execution policy `policy`.

- `template <class UnaryPredicate> void filter(UnaryPredicate&& predicate) &`: Modifies the collection,
  removing elements for which the unary predicate `predicate` returns false. The filtering is performed sequentially.

- `template <class UnaryPredicate> Collection filtered(UnaryPredicate&& predicate) &&`: Modifies the
  collection and returns a reference to the modified collection using move semantics, removing elements for which the
  unary predicate `predicate` returns false. The filtering is performed sequentially.

- `template <class UnaryPredicate> Collection filtered(UnaryPredicate&& predicate) const&`:
  Creates a copy of the collection and applies filtering to the copy. The original collection is unchanged. The
  filtering is performed sequentially.

## Transform

- `template <class ExecutionPolicy, class UnaryOperation> auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) &&`:
  Transforms the elements in the collection using the provided unary operation `op`. The result of the transformation
  is stored in a new `Collection`. The transformation is performed using the specified execution
  policy `policy`.

- `template <class ExecutionPolicy, class UnaryOperation> auto transform(ExecutionPolicy&& policy, UnaryOperation&& op) const&`:
  Transforms the elements in the collection using the provided unary operation `op`. The result of the transformation
  is stored in a new `Collection`. A copy of the collection is made for the transformation process to keep the original
  collection unchanged. The transformation is performed using the specified execution policy `policy`.

- `template <class UnaryOperation> auto transform(UnaryOperation&& op) &&`: Transforms the
  elements in the collection using the provided unary operation `op`. The result of the transformation is stored in a
  new `Collection`. The transformation is performed sequentially.

- `template <class UnaryOperation> auto transform(UnaryOperation&& op) const&`: Transforms the
  elements in the collection using the provided unary operation `op`. The result of the transformation is stored in a
  new `Collection`. A copy of the collection is made for the transformation process to keep the original collection
  unchanged. The transformation is performed sequentially.

## Flat Transform

> **Note**: These methods are only available if the elements in the collection satisfy the `std::ranges::range` concept
> and does not use `std::array` as the underlying container type.

- `template <class ExecutionPolicy, class UnaryOperation> auto flat_transform(ExecutionPolicy&& policy, UnaryOperation&& op) &&`:
  Flattens and transforms the elements in the collection using the provided unary operation `op`. The result of the
  transformation is stored in a new `Collection`. The transformation is performed using the specified
  execution policy `policy`.

- `template <class ExecutionPolicy, class UnaryOperation> auto flat_transform(ExecutionPolicy&& policy, UnaryOperation&& op)
  const&`: Flattens and transforms the elements in the collection using the provided unary operation `op`. The result of
  the transformation is stored in a new `Collection`. A copy of the collection is made for the transformation process to
  keep the original collection unchanged. The transformation is performed using the specified execution
  policy `policy`.

- `template <class UnaryOperation> auto flat_transform(UnaryOperation&& op) &&`: Flattens and transforms the elements in
  the collection using the provided unary operation `op`. The result of the transformation is stored in a
  new `Collection`. The transformation is performed sequentially.

- `template <class UnaryOperation> auto flat_transform(UnaryOperation&& op) const&`: Flattens and transforms the
  elements in the collection using the provided unary operation `op`. The result of the transformation is stored in a
  new `Collection`. A copy of the collection is made for the transformation process to keep the original collection
  unchanged. The transformation is performed sequentially.

## Sorts

- `template <class ExecutionPolicy, class Cmp> void sort(ExecutionPolicy&& policy, Cmp cmp) &`: Sorts the
  elements in the collection using the provided comparison function `cmp`. The sorting is performed using
  the specified execution policy `policy`.

- `template <class ExecutionPolicy, class Cmp> Collection sorted(ExecutionPolicy&& policy, Cmp cmp) &&`:
  Sorts the elements in the collection using the provided comparison function `cmp`. The original collection is
  modified using move semantics during the sorting process. The sorting is performed using the specified execution
  policy `policy`.

- `template <class ExecutionPolicy, class Cmp> Collection sorted(ExecutionPolicy&& policy, Cmp cmp) const&`:
  Creates a copy of the collection and sorts the copy using the provided comparison function `cmp`. The original
  collection is unchanged. The sorting is performed using the specified execution policy `policy`.

- `template <class Cmp = std::ranges::less> void sort(Cmp cmp = {}) &`: Sorts the elements in the collection
  using the default comparison function `std::ranges::less`. The sorting is performed sequentially.

- `template <class Cmp = std::ranges::less> Collection sorted(Cmp cmp = {}) &&`: Sorts the elements in the
  collection using the default comparison function `std::ranges::less`. The original collection is modified using move
  semantics during the sorting process. The sorting is performed sequentially.

- `template <class Cmp = std::ranges::less> Collection sorted(Cmp cmp = {}) const&`: Creates a
  copy of the collection and sorts the copy using the default comparison function `std::ranges::less`. The original
  collection is unchanged. The sorting is performed sequentially.

- `template <class ExecutionPolicy, class Cmp> void stable_sort(ExecutionPolicy&& policy, Cmp cmp) &`: Sorts
  the elements in the collection using the provided comparison function `cmp`. The sorting is stable, meaning that the
  relative order of equal elements is preserved. The sorting is performed using the specified execution
  policy `policy`.

- `template <class ExecutionPolicy, class Cmp> Collection stable_sorted(ExecutionPolicy&& policy, Cmp cmp) &&`:
  Sorts the elements in the collection using the provided comparison function `cmp`. The original collection is
  modified using move semantics during the sorting process. The sorting is stable, meaning that the relative order of
  equal elements is preserved. The sorting is performed using the specified execution policy `policy`.

- `template <class ExecutionPolicy, class Cmp> Collection stable_sorted(ExecutionPolicy&& policy, Cmp cmp) const&`:
  Creates a copy of the collection and sorts the copy using the provided comparison function `cmp`. The sorting is
  stable, meaning that the relative order of equal elements is preserved. The original collection is unchanged. The
  sorting is performed using the specified execution policy `policy`.

- `template <class Cmp = std::ranges::less> void stable_sort(Cmp cmp = {}) &`: Sorts the elements in the
  collection using the default comparison function `std::ranges::less`. The sorting is stable, meaning that the
  relative order of equal elements is preserved. The sorting is performed sequentially.

- `template <class Cmp = std::ranges::less> Collection stable_sorted(Cmp cmp = {}) &&`:
  Sorts the elements in the collection using the default comparison function `std::ranges::less`. The original
  collection is modified using move semantics during the sorting process. The sorting is stable, meaning that the
  relative order of equal elements is preserved. The sorting is performed sequentially.

- `template <class Cmp = std::ranges::less> Collection stable_sorted(Cmp cmp = {}) const&`:
  Creates a copy of the collection and sorts the copy using the default comparison function `std::ranges::less`. The
  sorting is stable, meaning that the relative order of equal elements is preserved. The original collection is
  unchanged. The sorting is performed sequentially.

## Reverse

- `template <class ExecutionPolicy> void reverse(ExecutionPolicy&& policy) &`: Reverses the order of elements
  in the collection in-place. The reversing is performed using the specified execution policy `policy`.

- `template <class ExecutionPolicy> Collection reversed(ExecutionPolicy&& policy) &&`: Reverses the order of elements
  in the collection in-place. The original collection is modified using move semantics during the reversing process. The
  reversing is performed using the specified execution policy `policy`.

- `template <class ExecutionPolicy> Collection reversed(ExecutionPolicy&& policy) const&`: Creates a copy of the
  collection and reverses the order of elements in the copy. The original collection is unchanged. The reversing is
  performed using the specified execution policy `policy`.

- `void reverse() &`: Reverses the order of elements in the collection in-place.

- `Collection reversed() &&`: Reverses the order of elements in the collection in-place. The original collection
  is modified using move semantics during the reversing process.

- `Collection reversed() const&`: Creates a copy of the collection and reverses the order of
  elements in the copy. The original collection is unchanged.

## Contains

- `bool contains(const value_type& value) const`: Returns `true` if the `value` is present in the collection,
  otherwise returns `false`.

- `template <class U> bool contains(const U& value) const`: A template overload of `contains` that allows
  checking if a value convertible to `value_type` is present in the collection. Returns `true` if the value is present,
  otherwise returns `false`.

## Implicit Conversions

- `explicit operator bool() const noexcept`: Converts the collection to a `bool` value. Returns `true` if the
  collection is not empty, otherwise returns `false`.

- `operator container_type() const&`: Converts the collection to the underlying container type (`container_type`) when
  used with a lvalue `Collection`.

- `operator container_type() &&`: Converts the collection to the underlying container type (`container_type`)
  when used with a rvalue `Collection`. This conversion allows moving the underlying container out of
  the `Collection`.

- `template <std::ranges::range R> operator R() const&`: Converts the collection to another range type (`R`) when used
  with a lvalue `Collection`. The elements are copied to the new range.

- `template <std::ranges::range R> operator R() &&`: Converts the collection to another range type (`R`) when
  used with a rvalue `Collection`. The elements are moved to the new range.

- `template <class F, class S> operator std::pair<F, S>() const&`: Converts the collection to a `std::pair<F, S>` when
  used with a lvalue `Collection`. The first two elements of the collection are used to initialize the pair.

- `template <class F, class S> operator std::pair<F, S>() &&`: Converts the collection to a `std::pair<F, S>` when used
  with a rvalue `Collection`. The first two elements of the collection are moved to initialize the pair.

- `template <class... Ts> operator std::tuple<Ts...>() const&`: Converts the collection to a `std::tuple<Ts...>` when
  used with a lvalue `Collection`. The first `sizeof...(Ts)` elements of the collection are used to initialize the
  tuple.

- `template <class... Ts> operator std::tuple<Ts...>() &&`: Converts the collection to a `std::tuple<Ts...>` when used
  with a rvalue `Collection`. The first `sizeof...(Ts)` elements of the collection are moved to initialize the tuple.

## Deduction Guides

- `template <class T, std::size_t N> Collection(T (&)[N]) -> Collection<T, std::array<T, N>>`: This deduction guide
  allows the Collection class to be deduced when the source data is a C-style array (T[N]).

- `template <class T, std::size_t N> Collection(const T (&)[N]) -> Collection<T, std::array<T, N>>`: Similar to the
  previous guide, this deduction guide covers const C-style arrays (const T[N]).

- `template <class T, std::size_t N> Collection(T (&&)[N]) -> Collection<T, std::array<T, N>>`: This guide handles
  rvalue C-style arrays (T(&&)[N]).

- `template <class T, std::size_t N> Collection(const T (&&)[N]) -> Collection<T, std::array<T, N>>`: This guide is for
  const rvalue C-style arrays (const T(&&)[N]).

- `template <class T, std::size_t N> Collection(std::array<T, N>&) -> Collection<T, std::array<T, N>>`: This deduction
  guide enables the Collection class to be deduced from an lvalue std::array.

- `template <class T, std::size_t N> Collection(const std::array<T, N>&) -> Collection<T, std::array<T, N>>`: This guide
  handles const lvalue std::array.

- `template <class T, std::size_t N> Collection(std::array<T, N>&&) -> Collection<T, std::array<T, N>>`: This guide is
  for rvalue std::array.

- `template <class T, std::size_t N> Collection(const std::array<T, N>&&) -> Collection<T, std::array<T, N>>`: This
  guide handles const rvalue std::array.

- `template <class T> Collection(std::initializer_list<T>) -> Collection<T>`: This deduction guide allows the Collection
  class to be deduced when using an initializer list.

- `template <class T> Collection(const std::vector<T>&) -> Collection<T, std::vector<T>>`: This guide handles const
  lvalue std::vector.

- `template <class T> Collection(std::vector<T>&&) -> Collection<T, std::vector<T>>`: This guide is for rvalue std::
  vector.

- `template <std::ranges::range R> Collection(R&&) -> Collection<std::remove_reference_t<std::ranges::range_reference_t<R>>>`:
  This guide enables the Collection class to be deduced from a range (R), making it compatible with various range-based
  data sources.
