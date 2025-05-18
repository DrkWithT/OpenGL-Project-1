#pragma once

#include <vector>

namespace GLProject1::Game {
    enum TileCode {
        air,
        wall,
        player,
        goal
    };

    /// @brief Represents a 1 unit hop in some direction.
    enum class BoardMove {
        up,
        down,
        left,
        right,
        last = right + 1
    };

    /// @brief This type actually represents locations or their offsets.
    struct BoardPair {
        int row;
        int col;
    };

    /// TODO: extend later to support other tiles.
    class Board {
    private:
        std::vector<std::vector<int>> m_data;

        int m_rows;
        int m_cols;
        int m_player_row;
        int m_player_col;
        int m_goal_row;
        int m_goal_col;

        BoardPair validateMove(BoardMove move) noexcept;

    public:
        Board(const std::vector<std::vector<int>>& data, BoardPair player_pos, BoardPair goal_pos);

        [[nodiscard]] int getRowCount() const noexcept;
        [[nodiscard]] int getColCount() const noexcept;

        [[nodiscard]] int getTile(int row, int col) const noexcept;

        void tryMove(BoardMove move);

        [[nodiscard]] bool isSolved() const noexcept;
    };
}