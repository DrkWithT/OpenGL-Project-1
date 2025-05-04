add_library(GLWraps "")
target_include_directories(GLWraps PUBLIC "${MY_HEADERS_DIR}")
target_sources(GLWraps PRIVATE ColorUtils.cpp PRIVATE BufferObjs.cpp PRIVATE ShaderUtils.cpp PRIVATE Window.cpp)
