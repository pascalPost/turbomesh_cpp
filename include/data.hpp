// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

#include <tuple>
#include <variant>
#include <vector>

namespace turbomesh
{

struct vector3d : std::tuple<double, double, double>
{
};

struct cartesian_vector3d : vector3d
{
};

struct cylindrical_vector3d : vector3d
{
};

using vector3d_var = std::variant<cartesian_vector3d, cylindrical_vector3d>;

struct blade_section
{
  std::vector<vector3d_var> suction_side;
  std::vector<vector3d_var> pressure_side;
};

struct blade
{
  std::vector<blade_section> sections;
};

} // namespace turbomesh