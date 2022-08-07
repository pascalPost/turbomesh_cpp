// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include "../../include/io/toml.hpp"
#include "../../include/error.hpp"
#include "../../include/io/csv.hpp"
#include "toml/value.hpp"
#include <toml.hpp>

namespace turbomesh
{

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

  auto name = toml::find<std::string>( toml_table, "name" );
  auto delimiter = toml::find<char>( toml_table, "delimiter" );

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
                 const toml::key& key )
{
  const toml::basic_value<C, M, V>& toml_table_hub_shroud =
    toml::find<toml::table>( toml_root, key );

  auto csv_file = read_csv_file( toml_table_hub_shroud );

  if ( !csv_file )
  {
    error( R"(Only supported for table "hub" and "shroud" : type = "csv")" );
  }

  auto point_data =
    read_csv_data( ( *csv_file ).name, ( *csv_file ).delimiter );

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
  auto bladed = toml::find<bool>( toml_table_row, "bladed" );
  auto nPassage = toml::find<unsigned>( toml_table_row, "passages" );

  std::optional<blade_t> blade{};

  if ( toml_table_row.contains( "blade" ) )
  {
    // blade = read_blade()
    error( "Bladed rows not yet implemented." );
  }

  return { std::move( name ), nPassage, std::move( blade ) };
}

/// read rows from toml file
std::vector<row_t>
read_rows( const auto& toml_root )
{
  const auto& blades = toml::find<toml::array>( toml_root, "blades" );

  const auto nBlade = blades.size();
  if ( nBlade < 1 )
  {
    error( R"(No array "blades" specified.)" );
  }

  std::vector<row_t> rows{};
  rows.reserve( nBlade );

  for ( const auto& blade : blades )
  {
    auto name = toml::find<std::string>( blade, "name" );
    auto suction_side = toml::find<std::vector<double>>( blade, "name" );
    auto row = read_row( blade );

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
geometry_t
read_geometry( const toml::basic_value<C, M, V>& toml_root )
{
  auto hub = read_hub_shroud( toml_root, "hub" );
  auto shroud = read_hub_shroud( toml_root, "shroud" );
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
  const auto toml_root = toml::parse( input_file );

  auto geometry = read_geometry( toml_root );

  return { std::move( geometry ) };
}

} // namespace turbomesh
