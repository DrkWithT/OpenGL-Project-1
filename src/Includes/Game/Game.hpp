#pragma once

#include "AppCtrl/KeyData.hpp"
#include "Game/Board.hpp"
#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/BufferObjs.hpp"
#include "GLWraps/ShaderUtils.hpp"

namespace GLProject1::Game {
    struct ColorSettings {
        GLWraps::ScaledRGBColor background;
        GLWraps::ScaledRGBColor wall;
        GLWraps::ScaledRGBColor player;
        GLWraps::ScaledRGBColor goal;
    };

    struct UniformNames {
        const char* stencil_name;
        const char* origin_name;
        const char* shrink_name;
        const char* place_tile_name;
    };

    /**
     * @brief A part of the Game class which renders the maze board.
     */
    class TileRenderer {
    public:
        TileRenderer(ColorSettings colors, GLWraps::Program&& shader_program, GLWraps::VAO&& tile_model, UniformNames uniform_names);

        void drawBoard(const Board& board, float window_width, float window_height);

    private:
        void drawTile(int row, int col, float tile_wpx, float tile_hpx, float window_width, float window_height, int tile_kind);

        ColorSettings m_colors;
        GLWraps::Program m_shader;
        GLWraps::VAO m_model;
        const char* m_stencil_uniform;
        const char* m_origin_uniform;
        const char* m_shrink_uniform;
        const char* m_placement_uniform;
    };

    /**
     * @brief Encapsulates game state: rendering & board data.
     */
    class Game {
    public:
        Game(ColorSettings settings, Board&& level, GLWraps::VAO&& tile_model, GLWraps::Program&& shader_program, UniformNames uniforms);

        /// NOTE: returns true / false for level-passing status!
        void processInput(AppCtrl::KeyCode key);

        void display(float window_width, float window_height);

        [[nodiscard]] bool isPassed() const noexcept;

    private:
        /// TODO: support multiple level progression!
        Board m_level;
        TileRenderer m_renderer;
        bool m_passed;
    };
}