//
// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 10/14/2023.
// Copyright (c) 2023 RobôCIn.
//

#include "robocin/geometry/rect2d.h"

namespace robocin {

template struct Rect2D<std::int16_t>;
template struct Rect2D<std::int32_t>;
template struct Rect2D<std::int64_t>;
template struct Rect2D<float>;
template struct Rect2D<double>;
template struct Rect2D<long double>;

} // namespace robocin
