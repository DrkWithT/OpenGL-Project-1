add_library(FileUtils "")
target_include_directories(FileUtils PUBLIC "${MY_HEADERS_DIR}")
target_sources(FileUtils PRIVATE Reading.cpp)
