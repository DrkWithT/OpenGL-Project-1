/**
 * @file Main.cpp
 * @author DrkWithT
 * @brief Implements driver logic for my tile maze game.
 * @version 0.0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include "FileUtils/Reading.hpp"
#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/Window.hpp"
#include "Game/LevelLoader.hpp"
#include "Game/Game.hpp"

using namespace GLProject1;

using MyIOStatus = FileUtils::ReadStatus;
using MyGLConfig = GLWraps::WindowGLConfig;
using MyProgram = GLWraps::Program;
using MyWindow = GLWraps::Window;
using MyPoint = GLWraps::PositionVertex;
using MyCallbackRefs = GLWraps::ServiceRefs;

constexpr const char* window_title = "Maze Demo";
constexpr int window_width = 480;
constexpr int window_height = 480;

constexpr MyGLConfig app_gl_hints {
    3,    // OpenGL major version (3)
    3,    // OpenGL minor version (3)
    1     // GLFW frame swap interval (1)
};

constexpr const char* vertex_shader_path = "./shaders/vertex_shader.glsl";
constexpr const char* fragment_shader_path = "./shaders/fragment_shader.glsl";

/// NOTE: contains 2d tile geometry
const GLWraps::MeshData mesh_1 {
    GLWraps::VertexStore {{
    MyPoint {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f}}},
    /// NOTE: point indexes per primitive (top left, bottom right triangles)
    {
        0, 1, 3,
        1 ,2, 3
    }
};

/// NOTE: air is white
const GLWraps::ScaledRGBColor bg_color = GLWraps::toScaledRGB({
    255,
    255,
    255
});

/// NOTE: tiles are dark gray
const GLWraps::ScaledRGBColor wall_color = GLWraps::toScaledRGB({
    120,
    120,
    120
});

/// NOTE: player is pastel orange
const GLWraps::ScaledRGBColor player_color = GLWraps::toScaledRGB({
    255,
    180,
    80
});

/// NOTE: goal is reddish
const GLWraps::ScaledRGBColor goal_color = GLWraps::toScaledRGB({
    240,
    100,
    100
});


/// NOTE: Only set the global reference holder to an instance referencing a local Window & Game in main()!! This is a workaround to make GLFW callbacks play nicer with Game & Window wrappers.
static GLWraps::ServiceRefs* refs = nullptr;

[[nodiscard]] MyProgram compileProgramWith(const char* vs_path_cstr, const char* fs_path_cstr) {
    const auto [vs_src, vs_read_status] = FileUtils::readFileSync(vs_path_cstr);

    if (vs_read_status != MyIOStatus::ok) {
        FileUtils::reportError(vs_read_status);
        return MyProgram::makeProgram();
    }

    const auto [fs_src, fs_read_status] = FileUtils::readFileSync(fs_path_cstr);

    if (fs_read_status != MyIOStatus::ok) {
        FileUtils::reportError(fs_read_status);
        return MyProgram::makeProgram();
    }

    return MyProgram::makeProgram(vs_src.c_str(), fs_src.c_str());
}

void onWindowResize([[maybe_unused]] GLFWwindow* window_ptr, int width, int height) {
    refs->refWindow()->setViewingDims(width, height);
}

void onKeyPress([[maybe_unused]] GLFWwindow* window_ptr, int keycode, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int modifiers) {
    if (action != GLFW_PRESS) {
        return;
    }

    switch (keycode) {
    case GLFW_KEY_UP:
        refs->refGameState()->processInput(AppCtrl::KeyCode::key_arrow_up);
        break;
    case GLFW_KEY_DOWN:
        refs->refGameState()->processInput(AppCtrl::KeyCode::key_arrow_down);
        break;
    case GLFW_KEY_LEFT:
        refs->refGameState()->processInput(AppCtrl::KeyCode::key_arrow_left);
        break;
    case GLFW_KEY_RIGHT:
        refs->refGameState()->processInput(AppCtrl::KeyCode::key_arrow_right);
        break;
    default:
        break;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: ./game <level-file-path>\n";
        return 1;
    }

    const auto& [tiles, spawn_row, spawn_col, goal_row, goal_col] = Game::load_level(argv[1]);

    if (spawn_row == -1 || spawn_col == -1 || goal_row == -1 || goal_col == -1 || tiles.size() == 0) {
        std::cerr << "Invalid level: tile matrix empty OR player and/or goal tile data missing.\n";
        return 1;
    }

    MyWindow app_window {window_title, window_width, window_height, app_gl_hints};
    Game::Game game_state {
        Game::ColorSettings {
            .background = bg_color,
            .wall = wall_color,
            .player = player_color,
            .goal = goal_color
        },
        Game::Board {
            tiles,
            Game::BoardPair {spawn_row, spawn_col},
            Game::BoardPair {goal_row, goal_col},
        },
        GLWraps::VAO {mesh_1},
        compileProgramWith(vertex_shader_path, fragment_shader_path),
        Game::UniformNames {
            "myColor",
            "originTransform", // projection mat4: NDC -> "canvas-origin" 2-D system
            "shrinkTransform",
            "placeTransform"
        }
    };

    MyCallbackRefs callback_utility_refs {&game_state, &app_window};
    refs = &callback_utility_refs;

    if (!app_window.isReady()) {
        std::cerr << "Invalid setup for window!\n";
        return 1;
    }

    if (!app_window.setResizeCallback(onWindowResize) || !app_window.setKeyCallback(onKeyPress)) {
        std::cerr << "Invalid setup for resize or keypress callback!\n";
        return 1;
    }

    app_window.displayGame(game_state);
}