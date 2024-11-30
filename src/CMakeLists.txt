set(MY_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Includes")
set(MY_EXTERNAL_SRCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Externals")

# add_subdirectory(OGLWraps)
# add_subdirectory(PicoLinAlg)

add_executable(glproject1)
target_include_directories(glproject1 PUBLIC "${MY_HEADERS_DIR}")
target_link_directories(glproject1 PRIVATE "${MY_LINK_DIR}")
target_link_libraries(glproject1 PRIVATE glad PRIVATE glfw.3.3)
target_sources(glproject1 PRIVATE Main.cpp "${MY_EXTERNAL_SRCS_DIR}/glad.c")
