# Copyright (c) Pascal Post. All Rights Reserved.
# Licensed under AGPLv3 license (see LICENSE.txt for details)

add_library(turbomesh SHARED
  src/io/toml.cpp
  src/io/csv.cpp
  )

include(../cmake/AddToml11.cmake)

target_link_libraries(turbomesh PUBLIC toml11::toml11)