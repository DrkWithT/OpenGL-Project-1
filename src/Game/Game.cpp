#include <utility>
#include "GLM/glm/mat4x4.hpp"
#include "GLM/glm/gtc/type_ptr.hpp"
#include "GLWraps/Uniform.hpp"
#include "Game/Game.hpp"

namespace GLProject1::Game {
    constexpr const char* stencil_uid = "myColor";
    constexpr const char* shrink_wd_uid = "shrinkWidthFactor";
    constexpr const char* shrink_hd_uid = "shrinkHeightFactor";
    constexpr const char* place_tile_uid = "placeTransform";

    TileRenderer::TileRenderer(ColorSettings colors, GLWraps::Program&& shader_program, GLWraps::VAO&& tile_model, const char* stencil_uniform_name, const char* shrink_width_uniform_name, const char* shrink_height_uniform_name, const char* tile_placement_uniform_name)
    : m_colors {colors}, m_shader {shader_program}, m_model {tile_model}, m_stencil_uniform {stencil_uniform_name}, m_width_shrink_uniform {shrink_width_uniform_name}, m_height_shrink_uniform {shrink_height_uniform_name}, m_placement_uniform {tile_placement_uniform_name} {}

    void TileRenderer::drawBoard(const Board& board, float window_width, float window_height) {
        // 1. clear background to air color 1st...
        const auto& [back_r, back_g, back_b] = m_colors.background;
        glClearColor(back_r, back_g, back_b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 2. Draw board's tiles...
        const auto row_n = board.getRowCount();
        const auto col_n = board.getColCount();
        const auto tile_wpx = window_width / row_n;
        const auto tile_hpx = window_height / col_n;

        for (int row_it = 0; row_it < row_n; row_it++) {
            for (int col_it = 0; col_it < col_n; col_it++) {
                drawTile(row_it, col_it, row_n, col_n, tile_wpx, tile_hpx, window_width, window_height, board.getTile(row_it, col_it));
            }
        }
    }

    void TileRenderer::drawTile(int row, int col, int downscale_width, int downscale_height, float tile_wpx, float tile_hpx, float window_width, float window_height, int tile_kind) {
        if (tile_kind == TileCode::air) {
            return; // mild optimization: don't draw air tiles!
        }

        // 1. get uniforms
        const GLWraps::glw_uniform_handle_t stencil = glGetUniformLocation(m_shader.getHandle(), m_stencil_uniform);
        const GLWraps::glw_uniform_handle_t width_shrink = glGetUniformLocation(m_shader.getHandle(), m_width_shrink_uniform);
        const GLWraps::glw_uniform_handle_t height_shrink = glGetUniformLocation(m_shader.getHandle(), m_width_shrink_uniform);
        const GLWraps::glw_uniform_handle_t placement = glGetUniformLocation(m_shader.getHandle(), m_placement_uniform);

        /// 2. Update uniforms: current tile color, shrink, and positioning...
        m_shader.useSelf();

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

        GLWraps::FloatUniform::updateData(width_shrink, static_cast<float>(downscale_width));
        GLWraps::FloatUniform::updateData(height_shrink, static_cast<float>(downscale_height));

        glm::mat4 placing_mat {1.0f};
        placing_mat = glm::translate(placing_mat, glm::vec3 {
            tile_hpx * static_cast<float>(row) / window_height,
            tile_wpx * static_cast<float>(col) / window_width,
            0.0f
        });

        GLWraps::T44Uniform::updateData(placement, glm::value_ptr(placing_mat));

        // 3. use draw calls!
        m_model.bindSelf();
        glDrawElements(GL_TRIANGLES, m_model.getIndexCount(), GL_UNSIGNED_INT, 0);
        m_model.unbindSelf();
    }

    Game::Game(ColorSettings settings, Board&& level, GLWraps::VAO&& tile_model, GLWraps::Program&& shader_program)
    : m_level {level}, m_renderer {settings, std::forward<GLWraps::Program&&>(shader_program), std::forward<GLWraps::VAO&&>(tile_model), stencil_uid, shrink_wd_uid, shrink_hd_uid, place_tile_uid} {}

    [[nodiscard]] bool Game::processInput(AppCtrl::KeyCode key, float window_width, float window_height) {
        // 1. decode key (U, D, L, R) -> movement id
        const auto key_dir = static_cast<int>(key);
        const BoardMove given_move = BoardMove {key_dir};

        // 2. attempt given movement
        m_level.tryMove(given_move);

        // 3. redraw board for user
        m_renderer.drawBoard(m_level, window_width, window_height);

        // 3. check for maze completion
        return m_level.isSolved();
    }
}