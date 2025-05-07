#include <utility>
#include "GLM/glm/mat4x4.hpp"
#include "GLM/glm/gtc/type_ptr.hpp"
#include "GLWraps/Uniform.hpp"
#include "Game/Game.hpp"

namespace GLProject1::Game {
    TileRenderer::TileRenderer(ColorSettings colors, GLWraps::Program&& shader_program, GLWraps::VAO&& tile_model, UniformNames uniform_names)
    : m_colors {colors}, m_shader {shader_program}, m_model {tile_model}, m_stencil_uniform {uniform_names.stencil_name}, m_origin_uniform {uniform_names.origin_name}, m_shrink_uniform {uniform_names.shrink_name}, m_placement_uniform {uniform_names.place_tile_name} {
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void TileRenderer::drawBoard(const Board& board, float window_width, float window_height) {
        // 1. use shader for board tile renders...
        m_shader.useSelf();

        // 2. clear background to air color 1st...
        const auto& [back_r, back_g, back_b] = m_colors.background;
        glClearColor(back_r, back_g, back_b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 2. Draw board's tiles...
        const auto row_n = board.getRowCount();
        const auto col_n = board.getColCount();
        const auto tile_wpx = window_width / col_n;
        const auto tile_hpx = window_height / row_n;

        for (int row_it = 0; row_it < row_n; row_it++) {
            for (int col_it = 0; col_it < col_n; col_it++) {
                drawTile(row_it, col_it, tile_wpx, tile_hpx, window_width, window_height, board.getTile(row_it, col_it));
            }
        }
    }

    void TileRenderer::drawTile(int row, int col, float tile_wpx, float tile_hpx, float window_width, float window_height, int tile_kind) {
        if (tile_kind == TileCode::air) {
            return; // mild optimization: don't draw air tiles!
        }

        // 1. Update uniforms: tile coloring, projection for tile's origin-relocation, and then tile positioning
        const GLWraps::glw_uniform_handle_t stencil = glGetUniformLocation(m_shader.getHandle(), m_stencil_uniform);
        const GLWraps::glw_uniform_handle_t origin = glGetUniformLocation(m_shader.getHandle(), m_origin_uniform);
        const GLWraps::glw_uniform_handle_t shrink = glGetUniformLocation(m_shader.getHandle(), m_shrink_uniform);
        const GLWraps::glw_uniform_handle_t placement = glGetUniformLocation(m_shader.getHandle(), m_placement_uniform);

        switch (tile_kind) {
            case 1:
                GLWraps::RGBUniform::updateData(stencil, m_colors.wall.r, m_colors.wall.g, m_colors.wall.b);
                break;
            case 2:
                GLWraps::RGBUniform::updateData(stencil, m_colors.player.r, m_colors.player.g, m_colors.player.b);
                break;
            case 3:
                GLWraps::RGBUniform::updateData(stencil, m_colors.goal.r, m_colors.goal.g, m_colors.goal.b);
                break;
            default:
                break;
        }

        glm::mat4 origin_transform = glm::ortho(0.0f, static_cast<float>(window_width), static_cast<float>(window_height), 0.0f, -1.0f, 1.0f);
        GLWraps::T44Uniform::updateData(origin, glm::value_ptr(origin_transform));

        glm::mat4 shrink_transform {1.0f};
        shrink_transform = glm::scale(shrink_transform, glm::vec3 {tile_wpx, tile_hpx, 1.0f});

        GLWraps::T44Uniform::updateData(shrink, glm::value_ptr(shrink_transform));

        glm::mat4 placing_mat {1.0f};
        placing_mat = glm::translate(placing_mat, glm::vec3 {
            tile_wpx * static_cast<float>(col),
            tile_hpx * static_cast<float>(row),
            0.0f
        });
        GLWraps::T44Uniform::updateData(placement, glm::value_ptr(placing_mat));

        // 3. use draw calls!
        m_model.bindSelf();
        glDrawElements(GL_TRIANGLES, m_model.getIndexCount(), GL_UNSIGNED_INT, 0);
        m_model.unbindSelf();
    }

    Game::Game(ColorSettings settings, Board&& level, GLWraps::VAO&& tile_model, GLWraps::Program&& shader_program, UniformNames uniforms)
    : m_level {std::move(level)}, m_renderer {settings, std::forward<GLWraps::Program&&>(shader_program), std::forward<GLWraps::VAO&&>(tile_model), uniforms}, m_passed {false} {}

    void Game::processInput(AppCtrl::KeyCode key) {
        // 1. decode key (U, D, L, R) -> movement id
        const auto key_dir = static_cast<int>(key);
        const BoardMove given_move = BoardMove {key_dir};

        // 2. attempt given movement
        m_level.tryMove(given_move);

        // 3. check for maze completion
        m_passed = m_level.isSolved();
    }

    void Game::display(float window_width, float window_height) {
        // 4. redraw board for user
        m_renderer.drawBoard(m_level, window_width, window_height);
    }

    bool Game::isPassed() const noexcept {
        return m_passed;
    }
}