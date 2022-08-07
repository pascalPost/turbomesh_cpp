# Copyright (c) Pascal Post. All Rights Reserved.
# Licensed under AGPLv3 license (see LICENSE.txt for details)

add_executable(turbomesh_tests src/io/csv.cpp)
add_dependencies(turbomesh_tests turbomesh)
target_include_directories(turbomesh_tests PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)
target_link_libraries(turbomesh_tests PUBLIC turbomesh)

include(../cmake/AddCatch2.cmake)

target_link_libraries(turbomesh_tests PRIVATE Catch2::Catch2WithMain)