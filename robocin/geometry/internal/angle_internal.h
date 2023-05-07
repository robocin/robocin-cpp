//
// Created by José Cruz <joseviccruz> on 13/04/23.
// Copyright (c) 2023 RobôCIn.
//

#ifndef ROBOCIN_GEOMETRY_INTERNAL_ANGLE_INTERNAL_H
#define ROBOCIN_GEOMETRY_INTERNAL_ANGLE_INTERNAL_H

#include <concepts>

namespace robocin::angle_internal {

template <class F, class G>
concept other_floating_point = std::floating_point<G> and not std::same_as<F, G>;

} // namespace robocin::angle_internal

#endif // ROBOCIN_GEOMETRY_INTERNAL_ANGLE_INTERNAL_H
