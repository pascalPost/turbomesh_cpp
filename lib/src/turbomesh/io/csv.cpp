// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include "../../include/io/csv.hpp"
#include "../../include/error.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace turbomesh
{

/// @brief checks if number is a floating point number, see
/// https://stackoverflow.com/questions/447206/c-isfloat-function
bool
is_float( std::string token )
{
  std::istringstream iss( token );
  double d;
  iss >> std::noskipws >> d; // noskipws considers leading whitespace invalid
  // Check the entire string was consumed and if either failbit or badbit is set
  return iss.eof() && !iss.fail();
}

std::vector<std::string>
tokenize( std::string& line, const char delimiter )
{
  std::vector<std::string> tokens;
  tokens.reserve( 20 );

  // tokenize line
  std::stringstream lineStream( line );
  std::string token;

  while ( std::getline( lineStream, token, delimiter ) )
  {
    tokens.push_back( token );
  }

  tokens.shrink_to_fit();

  return tokens;
}

csv_data_t
read_csv_data( std::istream& file_contents,
               const char delimiter,
               const std::string& file_name )
{
  std::string header;
  std::getline( file_contents, header );

  if ( header.empty() )
  {
    error( "No header given in " + file_name );
  }

  const auto column_names = tokenize( header, delimiter );

  // check column names
  for ( const auto& name : column_names )
  {
    if ( is_float( name ) )
    {
      error( "Error in csv " + file_name + " : does not contain a header." );
    }
  }

  std::vector<std::vector<double>> data;
  data.reserve( 10000 ); // reserve 10000 lines

  std::string row;
  while ( std::getline( file_contents, row ) )
  {
    // ignore empty lines
    if ( row.empty() )
    {
      continue;
    }

    const auto tokens = tokenize( row, delimiter );

    if ( tokens.size() != column_names.size() )
    {
      error( "Error in csv " + file_name + " : column number mismatch." );
    }

    std::vector<double> row_data;
    row_data.reserve( tokens.size() );

    for ( const auto& token : tokens )
    {
      if ( !is_float( token ) )
      {
        error( "Error in csv " + file_name +
               " : non floating point data encountered ( " + token + " )." );
      }
      row_data.emplace_back( std::stod( token.c_str() ) );
    }

    data.emplace_back( std::move( row_data ) );
  }

  data.shrink_to_fit();

  return { std::move( column_names ), std::move( data ) };
}

csv_data_t
read_csv_data( const std::string& file_name, const char delimiter )
{
  // check if file exists
  if ( !std::filesystem::exists( file_name ) )
  {
    error( "Requested file " + file_name + " does not exist." );
  }

  std::ifstream file( file_name );
  return read_csv_data( file, delimiter, file_name );
}

} // namespace turbomesh