#include <catch2/catch_test_macros.hpp>

#include <io/csv.hpp>

SCENARIO( "a simple csv file can be parsed", "[csv]" )
{
  GIVEN(
    "The contents of a csv file with white space delimiter as a sting stream" )
  {
    std::stringstream ss;
    ss << "axial radial\n"
       << "-12.0 18.0\n"
       << "12.0 18";

    WHEN( "The stream is parsed as a csv file" )
    {
      turbomesh::csv_data_t csv_data = turbomesh::read_csv_data( ss, ' ' );

      THEN( "The column names must be parsed correctly" )
      {
        REQUIRE( csv_data.column_names.size() == 2 );
        REQUIRE( csv_data.column_names[0] == "axial" );
        REQUIRE( csv_data.column_names[1] == "radial" );
      }

      THEN( "The data must contain two rows" )
      {
        REQUIRE( csv_data.data.size() == 2 );
      }

      THEN( "The first row must contain 2 columns" )
      {
        REQUIRE( csv_data.data[0].size() == 2 );
      }

      THEN( "The second row must contain 2 columns" )
      {
        REQUIRE( csv_data.data[1].size() == 2 );
      }

      THEN( "The data must be parsed correctly" )
      {
        REQUIRE( csv_data.data[0][0] == -12.0 );
        REQUIRE( csv_data.data[0][1] == 18 );
        REQUIRE( csv_data.data[1][0] == 12.0 );
        REQUIRE( csv_data.data[1][1] == 18 );
      }
    }
  }

  GIVEN( "The contents of a csv file with white space delimiter and trailing "
         "white spaces as a sting stream" )
  {
    std::stringstream ss;
    ss << "axial radial \n"
       << "-12.0 18.0 \n"
       << "12.0 18 " << std::endl;

    WHEN( "The stream is parsed as a csv file" )
    {
      turbomesh::csv_data_t csv_data = turbomesh::read_csv_data( ss, ' ' );

      THEN( "The column names must be parsed correctly" )
      {
        REQUIRE( csv_data.column_names.size() == 2 );
        REQUIRE( csv_data.column_names[0] == "axial" );
        REQUIRE( csv_data.column_names[1] == "radial" );
      }

      THEN( "The data must contain two rows" )
      {
        REQUIRE( csv_data.data.size() == 2 );
      }

      THEN( "The first row must contain 2 columns" )
      {
        REQUIRE( csv_data.data[0].size() == 2 );
      }

      THEN( "The second row must contain 2 columns" )
      {
        REQUIRE( csv_data.data[1].size() == 2 );
      }

      THEN( "The data must be parsed correctly" )
      {
        REQUIRE( csv_data.data[0][0] == -12.0 );
        REQUIRE( csv_data.data[0][1] == 18 );
        REQUIRE( csv_data.data[1][0] == 12.0 );
        REQUIRE( csv_data.data[1][1] == 18 );
      }
    }
  }

  GIVEN( "The contents of a csv file with white space delimiter, trailing "
         "white spaces and a trailing new line as a sting stream" )
  {
    std::stringstream ss;
    ss << "axial radial \n"
       << "-12.0 18.0 \n"
       << "12.0 18 \n"
       << std::endl;

    WHEN( "The stream is parsed as a csv file" )
    {
      turbomesh::csv_data_t csv_data = turbomesh::read_csv_data( ss, ' ' );

      THEN( "The column names must be parsed correctly" )
      {
        REQUIRE( csv_data.column_names.size() == 2 );
        REQUIRE( csv_data.column_names[0] == "axial" );
        REQUIRE( csv_data.column_names[1] == "radial" );
      }

      THEN( "The data must contain two rows" )
      {
        REQUIRE( csv_data.data.size() == 2 );
      }

      THEN( "The first row must contain 2 columns" )
      {
        REQUIRE( csv_data.data[0].size() == 2 );
      }

      THEN( "The second row must contain 2 columns" )
      {
        REQUIRE( csv_data.data[1].size() == 2 );
      }

      THEN( "The data must be parsed correctly" )
      {
        REQUIRE( csv_data.data[0][0] == -12.0 );
        REQUIRE( csv_data.data[0][1] == 18 );
        REQUIRE( csv_data.data[1][0] == 12.0 );
        REQUIRE( csv_data.data[1][1] == 18 );
      }
    }
  }

  GIVEN( "The contents of a csv file with wrong number of entries in one line" )
  {
    std::stringstream ss;
    ss << "axial radial \n"
       << "-12.0 18.0 \n"
       << "12.0 12.0 18 \n"
       << std::endl;

    WHEN( "The stream is parsed as a csv file" )
    {
      REQUIRE_THROWS( turbomesh::read_csv_data( ss, ' ' ) );
    }
  }

  GIVEN( "The contents of a csv file containing a string entry" )
  {
    std::stringstream ss;
    ss << "axial radial \n"
       << "-12.0 18.0 \n"
       << "12.0 wrong \n"
       << std::endl;

    WHEN( "The stream is parsed as a csv file" )
    {
      REQUIRE_THROWS( turbomesh::read_csv_data( ss, ' ' ) );
    }
  }
}