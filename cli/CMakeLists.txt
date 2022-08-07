# Copyright (c) Pascal Post. All Rights Reserved.
# Licensed under AGPLv3 license (see LICENSE.txt for details)

add_executable(turbomesh_cli
  src/main.cpp
  src/arguments.cpp
  )

add_dependencies(turbomesh_cli turbomesh)
target_include_directories(turbomesh_cli PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)
target_link_libraries(turbomesh_cli PUBLIC turbomesh)

include(../cmake/AddCxxOpts.cmake)

target_link_libraries(turbomesh_cli PUBLIC cxxopts)