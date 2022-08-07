// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include "../include/arguments.hpp"
#include <data.hpp>
#include <io/toml.hpp>

int
main( int argc, const char* argv[] )
{
  const auto input_file = turbomesh::parse_arugments( argc, argv );

  turbomesh::data_t data = turbomesh::read_input_toml( input_file );

  return EXIT_SUCCESS;
}
