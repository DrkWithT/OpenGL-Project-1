cmake_minimum_required(VERSION 3.16)

project(GLSample3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (BUILD_DBG)
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-deprecated -Werror -g -Og)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-deprecated -Werror -O2)
endif()

add_subdirectory(src)
