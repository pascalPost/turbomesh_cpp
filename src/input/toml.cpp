// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#include <toml.hpp>
#include <string>

#include <iostream>

void read_input_toml(const std::string& file){
    const auto data  = toml::parse(file);
    const auto title = toml::find<std::string>(data, "title");
    std::cout << "the title is " << title << std::endl;
}