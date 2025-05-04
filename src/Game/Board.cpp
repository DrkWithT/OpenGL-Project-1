#include <array>
#include "Game/Board.hpp"

namespace GLProject1::Game {
    constexpr std::array<BoardPair, static_cast<std::size_t>(BoardMove::last)> directions = {
        BoardPair {-1, 0}, // up
        {1, 0}, // down
        {0, -1}, // left
        {0, 1} // right
    };

    constexpr BoardPair standstill {
        0,
        0
    };

    BoardPair Board::validateMove(BoardMove move) noexcept {
        /// NOTE: disallow invalid move kinds (last is for max-value of enum class BoardMove)!
        if (move == BoardMove::last) {
            return standstill;
        }

        const auto move_id = static_cast<int>(move);
        
        const auto [row_diff, col_diff] = directions[move_id];
        const auto target_row = m_player_row + row_diff;
        const auto target_col = m_player_col + col_diff;

        /// NOTE: allows movement into non-opaque tiles!
        if (m_data[target_row][target_col] == TileCode::air || m_data[target_row][target_col] == TileCode::goal) {
            return {row_diff, col_diff};
        }

        return standstill;
    }

    Board::Board(std::vector<std::vector<int>>&& data, BoardPair player_pos, BoardPair goal_pos)
    : m_data {data}, m_rows (m_data.size()), m_cols (m_data[0].size()), m_player_row {player_pos.row}, m_player_col {player_pos.col}, m_goal_row {goal_pos.row}, m_goal_col {goal_pos.col} {}

    int Board::getRowCount() const noexcept {
        return m_rows;
    }

    int Board::getColCount() const noexcept {
        return m_cols;
    }

    int Board::getTile(int row, int col) const noexcept {
        return m_data[row][col];
    }

    void Board::tryMove(BoardMove move) {
        const auto [row_move, col_move] = validateMove(move);

        m_player_row += row_move;
        m_player_col += col_move;
    }

    bool Board::isSolved() const noexcept {
        return m_player_row == m_goal_row && m_player_col == m_goal_col;
    }
}