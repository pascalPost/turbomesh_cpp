// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include <cstdlib>
#include <cxxopts.hpp>
#include <iostream>
#include <string>

namespace turbomesh
{

std::string
parse_arugments(const int argc, const char* argv[])
{
  cxxopts::Options options{ "turbomesh",
                            "Opensource turbomachiner grid tool." };

  options.add_options()("h,help", "Print usage")(
    "inputFile",
    "The input file in TOML format describing the configuration",
    cxxopts::value<std::string>());

  options.parse_positional({ "inputFile" });

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(EXIT_SUCCESS);
  }

  if (result["inputFile"].count() == 0)
  {
    std::cout << options.help() << std::endl;
    exit(EXIT_FAILURE);
  }

  return result["inputFile"].as<std::string>();
}

} // namespace turbomesh