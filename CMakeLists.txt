cmake_minimum_required(VERSION 3.19)

project(OGLProject1)

# NOTE: YOU MUST use the given CMake presets!

if (DO_DEBUG_BUILD)
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-deprecated -Werror -g -Og)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-deprecated -Werror -O2)
endif()

set(MY_LINK_DIR "${CMAKE_SOURCE_DIR}/lib")
add_subdirectory(src)
