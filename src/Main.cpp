/**
 * @file Main.cpp
 * @author DrkWithT
 * @brief Implements main rendering logic for a possible colliding block simulator.
 * @version 0.0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "FileUtils/Reading.hpp"
#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/Window.hpp"

using namespace GLProject1;

using MyIOStatus = FileUtils::ReadStatus;
using MyGLConfig = GLWraps::WindowGLConfig;
using MyProgram = GLWraps::Program;
using MyRenderer = GLWraps::Renderer;
using MyWindow = GLWraps::Window;
using MyPoint = GLWraps::PositionVertex;

constexpr const char* window_title = "Project 1";
constexpr int window_width = 480;
constexpr int window_height = 480;

constexpr MyGLConfig app_gl_hints {
    3,    // OpenGL major version (3)
    3,    // OpenGL minor version (3)
    1     // GLFW frame swap interval (1)
};

constexpr const char* vertex_shader_path = "./shaders/vertex_shader.glsl";
constexpr const char* fragment_shader_path = "./shaders/fragment_shader.glsl";

/// NOTE: main square
const GLWraps::MeshData mesh_1 {
    GLWraps::VertexStore {{
    MyPoint {-0.25f, 0.25f, 0.0f},
    {0.25f, 0.25f, 0.0f},
    {0.25f, -0.25f, 0.0f},
    {-0.25f, -0.25f, 0.0f}}},
    /// NOTE: point indexes per primitive (triangles of top left, bottom right)
    {
        0, 1, 3,
        1 ,2, 3
    }
};

/// NOTE: color is dark gray
const GLWraps::ScaledRGBColor bg_color = GLWraps::toScaledRGB({
    120,
    120,
    120
});

/// NOTE: pastel orange
const GLWraps::ScaledRGBColor color_1 = GLWraps::toScaledRGB({
    255,
    180,
    80
});

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

int main() {
    MyWindow app_window {window_title, window_width, window_height, 1, app_gl_hints};
    MyRenderer app_renderer {
        GLWraps::makeScene({
            GLWraps::Mesh {mesh_1, color_1}
        }, bg_color),
        compileProgramWith(vertex_shader_path, fragment_shader_path),
        "myColor",
        "dTransform"
    };

    if (!app_window.isReady() || !app_renderer.isReady()) {
        return -1;
    }

    app_window.displayScene(app_renderer);
}