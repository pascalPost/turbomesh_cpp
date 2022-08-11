// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

#include "../data.hpp"
#include <string>

namespace turbomesh
{

/// create the data_t from given input toml file
data_t
read_input_toml(const std::string& file);

} // namespace turbomesh