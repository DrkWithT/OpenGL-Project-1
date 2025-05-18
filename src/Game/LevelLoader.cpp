#include <string>
#include <sstream>
#include <fstream>
#include "Game/Board.hpp"
#include "Game/LevelLoader.hpp"

namespace GLProject1::Game {
    constexpr const char* end_name = "END";
    constexpr auto dud_coord = -1;
    constexpr BoardPair dud_pair = {dud_coord, dud_coord};

    LoadResult load_level(const char* file_path_cstr) {
        auto find_first_of = [](const std::vector<std::vector<int>>& tiles, int target) {
            int row_i = 0;
            int col_i = 0;

            for (const auto& row : tiles) {
                for (const auto& cell : row) {
                    if (cell == target) {
                        return BoardPair {
                            .row = row_i,
                            .col = col_i
                        };
                    }
                    ++col_i;
                }
                ++row_i;
            }

            return dud_pair;
        };

        std::ifstream reader {file_path_cstr};

        if (!reader.is_open()) {
            return {{}, dud_coord, dud_coord, dud_coord, dud_coord};
        }

        Tiles tiles;

        std::istringstream strin;
        std::string line;
        std::string token;

        while (std::getline(reader, line)) {
            strin.str(line);

            strin >> token;

            if (token == end_name) {
                break;
            } else {
                std::vector<int> tile_row = {};
                int temp = 0;

                while (strin >> temp) {
                    tile_row.push_back(temp);
                }

                tiles.emplace_back(tile_row);
            }
        }

        const auto [spawn_rc, spawn_cc] = find_first_of(tiles, TileCode::player);
        const auto [goal_rc, goal_cc] = find_first_of(tiles, TileCode::goal);

        return {
            tiles,
            spawn_rc,
            spawn_cc,
            goal_rc,
            goal_cc
        };
    }
}
