# Copyright (c) Pascal Post. All Rights Reserved.
# Licensed under AGPLv3 license (see LICENSE.txt for details)

cmake_minimum_required(VERSION 3.0.0)
project(turbomesh VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

add_executable(turbomesh
  src/main.cpp
  src/io/arguments.cpp
  src/io/toml.cpp
  src/io/csv.cpp
  )

target_link_libraries(turbomesh PRIVATE ${VTK_LIBRARIES})

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersGeneral
  IOInfovis
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Unable to find VTK.")
endif()

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS turbomesh
  MODULES ${VTK_LIBRARIES}
)

#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(cmake/AddCxxOpts.cmake)
include(cmake/AddToml11.cmake)

add_subdirectory(tests)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
