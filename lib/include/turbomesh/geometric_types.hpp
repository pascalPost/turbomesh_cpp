// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

#include <tuple>
#include <variant>

namespace turbomesh
{

// struct vector2d : std::tuple<double, double>
// {
// };

// struct cartesian_vector2d : vector2d
// {
// };

// struct cylindrical_vector2d : vector2d
// {
// };

struct vector3d : std::tuple<double, double, double>
{
  using std::tuple<double, double, double>::tuple;
};

struct cartesian_vector3d : vector3d
{
  using vector3d::vector3d;
};

struct cylindrical_vector3d : vector3d
{
  using vector3d::vector3d;
};

using vector3d_var = std::variant<cartesian_vector3d, cylindrical_vector3d>;

} // namespace turbomesh