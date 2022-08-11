// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include "../../include/io/toml.hpp"
#include "../../include/error.hpp"
#include "../../include/io/csv.hpp"
#include "toml/value.hpp"
#include <algorithm>
#include <filesystem>
#include <toml.hpp>

namespace turbomesh
{

template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
edge_clustering_t
read_edge_clustering( const toml::basic_value<C, M, V>& toml_row_mesh_table,
                      const toml::key& key )
{
  const toml::basic_value<C, M, V>& toml_table =
    toml::find<toml::table>( toml_row_mesh_table, key );

  const auto nPoint = toml::find<unsigned>( toml_table, "points" );
  const auto clustering_str =
    toml::find<std::string>( toml_table, "clustering" );

  if ( clustering_str != "equidistant" )
  {
    error( "Only equidistant clustering supported for now." );
  }

  equidistant_clustering_t clustering{};

  return { nPoint, std::move( clustering ) };
}

template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
single_block_topology_t
read_single_block_topology(
  const toml::basic_value<C, M, V>& toml_table_row_mesh )
{
  auto axial_edge_clustering =
    read_edge_clustering( toml_table_row_mesh, "axial" );
  auto radial_edge_clustering =
    read_edge_clustering( toml_table_row_mesh, "radial" );
  auto azimuth_edge_clustering =
    read_edge_clustering( toml_table_row_mesh, "azimuth" );

  return { std::move( axial_edge_clustering ),
           std::move( radial_edge_clustering ),
           std::move( azimuth_edge_clustering ) };
}

template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
topology_t
read_mesh( const toml::basic_value<C, M, V>& toml_table_row )
{
  const toml::basic_value<C, M, V>& toml_table_row_mesh =
    toml::find<toml::table>( toml_table_row, "mesh" );
  auto topology_str =
    toml::find<std::string>( toml_table_row_mesh, "topology" );

  if ( topology_str != "single_block" )
  {
    error( "Only single block topology supported for now." );
  }

  auto topology = read_single_block_topology( toml_table_row_mesh );

  return { std::move( topology ) };
}

/// read csv_file from toml file
template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
std::optional<csv_file_t>
read_csv_file( const toml::basic_value<C, M, V>& toml_table )
{
  auto type = toml::find<std::string>( toml_table, "type" );

  if ( type != "csv" )
  {
    return {};
  }

  auto name = toml::find<std::string>( toml_table, "file" );
  const auto delimiter_str = toml::find<std::string>( toml_table, "delimiter" );

  // check delimiter to be a char
  if ( delimiter_str.length() != 1 )
  {
    error( "The csv delimiter must be a single character." );
  }

  const char delimiter = delimiter_str[0];

  return csv_file_t{ std::move( name ), std::move( delimiter ) };
}

/// read hub_shroud_type from toml file
template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
hub_shroud_t
read_hub_shroud( const toml::basic_value<C, M, V>& toml_root,
                 const toml::key& key,
                 const std::filesystem::path& cwd )
{
  const toml::basic_value<C, M, V>& toml_table_hub_shroud =
    toml::find<toml::table>( toml_root, key );

  auto csv_file = read_csv_file( toml_table_hub_shroud );

  if ( !csv_file )
  {
    error( R"(Only supported for table "hub" and "shroud" : type = "csv")" );
  }

  const auto csv_file_path = cwd / ( *csv_file ).name;

  auto point_data =
    read_csv_data( csv_file_path.string(), ( *csv_file ).delimiter );

  // check column names
  if ( point_data.column_names[0] != "axial" ||
       point_data.column_names[1] != "radial" )
  {
    error(
      R"(csv file for "hub" and "shroud" must contain column names : axial radial)" );
  }

  // create points vector
  std::vector<cylindrical_vector3d> points;
  points.reserve( point_data.data.size() );

  for ( const auto& row : point_data.data )
  {
    points.emplace_back( row[0], row[1], 0 );
  }

  return { std::move( *csv_file ), std::move( points ) };
}

/// read row from array of tables named rows
row_t
read_row( const auto& toml_table_row )
{
  auto name = toml::find<std::string>( toml_table_row, "name" );
  auto nPassage = toml::find<unsigned>( toml_table_row, "passages" );

  std::optional<blade_t> blade{};

  if ( toml_table_row.contains( "blade" ) )
  {
    // blade = read_blade()
    error( "Bladed rows not yet implemented." );
  }

  auto mesh = read_mesh( toml_table_row );

  return { std::move( name ), nPassage, std::move( blade ), std::move( mesh ) };
}

/// read rows from toml file
std::vector<row_t>
read_rows( const auto& toml_root )
{
  const auto& rows_array = toml::find<toml::array>( toml_root, "rows" );

  const auto nRows = rows_array.size();
  if ( nRows < 1 )
  {
    error( R"(No array "rows" specified.)" );
  }

  std::vector<row_t> rows{};
  rows.reserve( nRows );

  for ( const auto& row_table : rows_array )
  {
    auto name = toml::find<std::string>( row_table, "name" );
    auto row = read_row( row_table );

    rows.emplace_back( std::move( row ) );
  }

  return rows;
}

/// read geometry from toml file
template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
setup_t
read_setup( const toml::basic_value<C, M, V>& toml_root,
            const std::filesystem::path& cwd )
{
  auto hub = read_hub_shroud( toml_root, "hub", cwd );
  auto shroud = read_hub_shroud( toml_root, "shroud", cwd );
  auto rows = read_rows( toml_root );

  return { std::move( hub ), std::move( shroud ), std::move( rows ) };
}

/// read data from toml file
template<typename C,
         template<typename...>
         class M,
         template<typename...>
         class V>
data_t
read_input_toml( const std::string& input_file )
{
  const toml::basic_value<C, M, V>& toml_root = toml::parse( input_file );

  auto geometry = read_geometry( toml_root );

  return { std::move( geometry ) };
}

/// read data from toml file
data_t
read_input_toml( const std::string& input_file )
{
  const std::filesystem::path input_file_path{ input_file };
  const auto cwd = input_file_path.parent_path();

  const auto toml_root = toml::parse( input_file );

  auto geometry = read_setup( toml_root, cwd );

  return { std::move( geometry ) };
}

} // namespace turbomesh
