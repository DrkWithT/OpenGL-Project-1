# add_subdirectory(Wrappers)

add_executable(glsample3)
target_include_directories(glsample3 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Includes")
target_link_directories(glsample3 PRIVATE "${CMAKE_SOURCE_DIR}/lib")
target_link_libraries(glsample3 PRIVATE glad PRIVATE glfw.3.3)
target_sources(glsample3 PRIVATE Main.cpp "${CMAKE_CURRENT_SOURCE_DIR}/Externals/glad.c")
