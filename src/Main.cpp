/**
 * @file Main.cpp
 * @author DrkWithT
 * @brief Implements main rendering logic.
 * @version 0.0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/Window.hpp"

using namespace GLProject1;

using MyGLConfig = GLWraps::WindowGLConfig;
using MyProgram = GLWraps::Program;
using MyRenderer = GLWraps::Renderer;
using MyWindow = GLWraps::Window;

/// TODO: replace this later when a Drawable ADT is made.
using MyPoint = GLWraps::PositionVertex;
using MyDrawable = GLWraps::Mesh;

constexpr const char* window_title = "Project 1";
constexpr int window_width = 480;
constexpr int window_height = 480;

constexpr MyGLConfig app_gl_hints {
    3,    // OpenGL major version (3)
    3,    // OpenGL minor version (3)
    1     // GLFW frame swap interval (1)
};

const GLWraps::MeshData draw_data {
    /// NOTE: points for square
    GLWraps::VertexStore {{
    MyPoint {0.5f, 0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {-0.5f, -0.5f, 0.0f},
    {-0.5f, 0.5f, 0.0f}}},
    /// NOTE: point indexes per primitive (triangles of top left, bottom right)
    {
        0, 1, 3,
        1 ,2 ,3
    }
};

constexpr const char* vtx_code = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

constexpr const char* frag_code = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(0.375f, 0.875f, 0.25f, 1.0f);\n"
    "}\n";

/// NOTE: color is dark gray
constexpr GLWraps::RGBColor background_color {
    120,
    120,
    120
};

/// NOTE: color is pastel orange
const GLWraps::ScaledRGBColor thing_color = GLWraps::toScaledRGB({
    255,
    180,
    80
});

int main() {
    MyWindow app_window {window_title, window_width, window_height, 1, app_gl_hints};
    MyRenderer app_renderer {MyProgram::makeProgram(vtx_code, frag_code), MyDrawable {draw_data, thing_color}, {background_color}};

    if (!app_window.isReady()) {
        return -1;
    }

    app_window.displayScene(app_renderer);
}