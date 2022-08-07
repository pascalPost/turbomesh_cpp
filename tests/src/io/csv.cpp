#include <catch2/catch_test_macros.hpp>

#include <io/csv.hpp>

SCENARIO( "a simple csv file can be parsed", "[csv]" )
{
  GIVEN( "The contents of a csv file as a sting stream" )
  {
    std::stringstream ss;
    ss << "axial radial\n"
       << "-12.0 18.0\n"
       << "12.0 18.0\n"
       << std::endl;

    WHEN( "The stream is parsed as a csv file" )
    {
      turbomesh::csv_data_t csv_data = turbomesh::read_csv_data( ss, ' ' );
    }
  }
}