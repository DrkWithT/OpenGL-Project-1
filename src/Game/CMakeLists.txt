add_library(Game "")
target_include_directories(Game PUBLIC ${MY_HEADERS_DIR})
target_sources(Game PRIVATE Board.cpp PRIVATE Game.cpp)
