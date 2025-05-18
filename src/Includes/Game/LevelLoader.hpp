#pragma once

#include <vector>

namespace GLProject1::Game {
    using Tiles = std::vector<std::vector<int>>;

    struct LoadResult {
        Tiles tiles;
        int spawn_row;
        int spawn_col;
        int goal_row;
        int goal_col;
    };

    [[nodiscard]] LoadResult load_level(const char* file_path_cstr);
}
