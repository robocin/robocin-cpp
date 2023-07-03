//
// Created by José Cruz <joseviccruz> on 07/04/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_UTILITY_CONCEPTS_H
#define ROBOCIN_UTILITY_CONCEPTS_H

#include <concepts>

namespace robocin {

template <class T>
concept arithmetic = std::is_arithmetic_v<T>;

} // namespace robocin

#endif // ROBOCIN_UTILITY_CONCEPTS_H
