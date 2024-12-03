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
using MyPoint = GLWraps::PositionVertex;

constexpr const char* window_title = "Project 1";
constexpr int window_width = 480;
constexpr int window_height = 480;

constexpr MyGLConfig app_gl_hints {
    3,    // OpenGL major version (3)
    3,    // OpenGL minor version (3)
    1     // GLFW frame swap interval (1)
};

constexpr const char* vtx_code = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

constexpr const char* frag_code = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec3 myColor;\n"
    "void main() {\n"
    "FragColor = vec4(myColor.xyz, 1.0f);\n"
    "}\n";

/// NOTE: top right square
const GLWraps::MeshData mesh_1 {
    GLWraps::VertexStore {{
    MyPoint {0.25f, 0.75f, 0.0f},
    {0.75f, 0.75f, 0.0f},
    {0.75f, 0.25f, 0.0f},
    {0.25f, 0.25f, 0.0f}}},
    /// NOTE: point indexes per primitive (triangles of top left, bottom right)
    {
        0, 1, 3,
        1 ,2 ,3
    }
};

/// NOTE: bottom right square
const GLWraps::MeshData mesh_2 {
    GLWraps::VertexStore {{
    MyPoint {-0.5f, -0.25f, 0.0f},
    {-0.25f, -0.25f, 0.0f},
    {-0.25f, -0.5f, 0.0f},
    {-0.5f, -0.5f, 0.0f}}},
    /// NOTE: point indexes per primitive (triangles of top left, bottom right)
    {
        0, 1, 3,
        1 ,2 ,3
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

/// NOTE: neon blue
const GLWraps::ScaledRGBColor color_2 = GLWraps::toScaledRGB({
    80,
    80,
    255
});

int main() {
    MyWindow app_window {window_title, window_width, window_height, 1, app_gl_hints};
    MyRenderer app_renderer {
        GLWraps::makeScene({
            GLWraps::Mesh {mesh_1, color_1},
            {mesh_2, color_2}
        }, bg_color),
        MyProgram::makeProgram(vtx_code, frag_code),
        "myColor"
    };

    if (!app_window.isReady()) {
        return -1;
    }

    app_window.displayScene(app_renderer);
}