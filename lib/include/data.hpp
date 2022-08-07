// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

#include "geometric_types.hpp"
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace turbomesh
{

struct csv_file_t
{
  std::string name;
  char delimiter;
};

struct edge_grid_parameter_t
{
  unsigned nPoint;
  // add variant of clustering
};

struct blade_section_t
{
  std::vector<vector3d_var> suction_side_points;
  std::vector<vector3d_var> pressure_side_points;
};

struct blade_t
{
  std::vector<blade_section_t> blade_sections;
};

struct row_t
{
  std::string name;
  unsigned nPassage;
  std::optional<blade_t> blade_opt;
};

struct hub_shroud_t
{
  csv_file_t csv_file;
  std::vector<cylindrical_vector3d> points;
};

struct geometry_t
{
  hub_shroud_t hub;
  hub_shroud_t shroud;
  std::vector<row_t> rows;
};

/// main data structure containing all turbomesh data
struct data_t
{
  geometry_t geometry;
};

} // namespace turbomesh