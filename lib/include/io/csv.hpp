// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

#include <string>
#include <vector>
namespace turbomesh
{

///@TODO add tests for csv parser based on file streams

/// data container for a csv with a single header row and numerical data
struct csv_data_t
{
  std::vector<std::string> column_names;
  std::vector<std::vector<double>> data;
};

/// reads a csv file
csv_data_t
read_csv_data( const std::string& file_name, const char delimiter );

/// parses a csv istream
csv_data_t
read_csv_data( std::istream& file_contents,
               const char delimiter,
               const std::string& file_name = {} );

} // namespace turbomesh