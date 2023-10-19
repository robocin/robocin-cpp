//
// Created by José Cruz <joseviccruz> on 29/07/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_COLLECTION_COLLECTION_INTERNAL_H
#define ROBOCIN_COLLECTION_COLLECTION_INTERNAL_H

#include <tuple>
#include <vector>

namespace robocin {

template <class T, class Container>
class Collection;

} // namespace robocin

namespace robocin::collection_internal {

// Assign a collection to a tuple helper functions -------------------------------------------------
template <std::size_t I, class T, class Container, class... Ts>
void assign(std::tuple<Ts...>& tuple, const Collection<T, Container>& collection) {
  if constexpr (I < sizeof...(Ts)) {
    using current_tuple_element_t = std::tuple_element_t<I, std::tuple<Ts...>>;
    static_assert(std::assignable_from<current_tuple_element_t&, T>);
    if (I < collection.size()) {
      std::get<I>(tuple) = collection[I];
      assign<I + 1, T, Container, Ts...>(tuple, collection);
    }
  }
}

template <class T, class Container, class... Ts>
void assign(std::tuple<Ts...>& tuple, const Collection<T, Container>& collection) {
  assign<0, T, Container, Ts...>(tuple, collection);
}

template <std::size_t I, class T, class Container, class... Ts>
void assign(std::tuple<Ts...>& tuple, Collection<T, Container>&& collection) {
  if constexpr (I < sizeof...(Ts)) {
    using current_tuple_element_t = std::tuple_element_t<I, std::tuple<Ts...>>;
    static_assert(std::assignable_from<current_tuple_element_t&, T>);
    if (I < collection.size()) {
      std::get<I>(tuple) = std::move(collection[I]);
      assign<I + 1, T, Container, Ts...>(tuple, std::move(collection));
    }
  }
}

template <class T, class Container, class... Ts>
void assign(std::tuple<Ts...>& tuple, Collection<T, Container>&& collection) {
  assign<0, T, Container, Ts...>(tuple, std::move(collection));
}

// ResultCollection helper functions ---------------------------------------------------------------
template <class...>
struct template_container;

template <class... Ts, template <class...> class Container>
struct template_container<Container<Ts...>> {
  template <class... Us>
  using type = Container<Us...>;
};

template <class T, std::size_t N, template <class, std::size_t> class Container>
struct template_container<Container<T, N>> {
  template <class U>
  using type = Container<U, N>;
};

template <class Container, class U>
using ResultCollection = Collection<U, typename template_container<Container>::template type<U>>;

} // namespace robocin::collection_internal

#endif // ROBOCIN_COLLECTION_COLLECTION_INTERNAL_H
