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

#include "GLWraps/Window.hpp"

using namespace GLProject1;

constexpr const char* window_title = "Project 1";
constexpr int window_width = 480;
constexpr int window_height = 480;
constexpr GLWraps::WindowGLConfig app_gl_hints {
    3,    // OpenGL major version (3)
    3,    // OpenGL minor version (3)
    1     // GLFW frame swap interval (1)
};

int main() {
    GLWraps::Window app_window {window_title, window_width, window_height, 1, app_gl_hints};

    if (!app_window.isReady()) {
        return -1;
    }

    app_window.displayScene();
}