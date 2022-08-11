// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include "../include/arguments.hpp"
#include <turbomesh/data.hpp>
#include <turbomesh/error.hpp>
#include <turbomesh/helper.hpp>
#include <turbomesh/io/toml.hpp>
#include <variant>

int
main( int argc, const char* argv[] )
{
  const auto input_file = turbomesh::parse_arugments( argc, argv );

  turbomesh::data_t data = turbomesh::read_input_toml( input_file );

  // grid generation

  // data.geometry.hub.points;

  for ( const auto& row : data.setup.rows )
  {
    if ( row.blade_opt )
    {
      turbomesh::error( "Bladed mesh rows not yet implemented." );
    }

    const auto& x_hub = data.setup.hub.points;
    const auto& x_shroud = data.setup.shroud.points;

    if ( x_hub.size() != 2 || x_shroud.size() != 2 )
    {
      turbomesh::error( "Only two point linear curve supported for now." );
    }

    const auto dx_hub = x_hub[1] - x_hub[0];
    const auto dx_shroud = x_shroud[1] - x_shroud[0];

    std::visit(
      turbomesh::overloaded{
        []( const turbomesh::single_block_topology_t& topo )
        {
          const auto nAxial = topo.axial.nPoint;

          std::visit(
            turbomesh::overloaded{
              []( const turbomesh::equidistant_clustering_t& equidistant )
              {
                const auto dx_hub_points = dx_hub / ;

                return x_axial;
              } },
            topo.axial.clustering );
        } },
      row.mesh.topology );
  }

  return EXIT_SUCCESS;
}
