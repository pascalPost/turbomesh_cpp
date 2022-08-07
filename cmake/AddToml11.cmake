# Copyright (c) Pascal Post. All Rights Reserved.
# Licensed under AGPLv3 license (see LICENSE.txt for details)

include(FetchContent)

FetchContent_Declare(
        toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG        v3.7.1
)

#cmake_policy(SET CMP0077 NEW)
#set(CMAKE_PROJECT_toml11_INCLUDE_BEFORE "${CMAKE_SOURCE_DIR}/cmake/CMP0077PolicyFix.cmake")
set(toml11_BUILD_TEST OFF)
FetchContent_MakeAvailable(toml11)

target_link_libraries(turbomesh PUBLIC toml11::toml11)