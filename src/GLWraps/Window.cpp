/**
 * @file Window.cpp
 * @author DrkWithT
 * @brief Implements GLFW window wrapper.
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include "GLAD3/glad.h"

#include "GLWraps/Window.hpp"

namespace GLProject1::GLWraps {
    void handleWindowResize([[maybe_unused]] GLFWwindow* raw_window, int new_width, int new_height) {
        glViewport(0, 0, new_width, new_height);
    }

    Window::Window() noexcept
    : m_win_handle {nullptr} {}

    Window::Window(const char* title, int width, int height, int swap_interval, WindowGLConfig gl_ctx_hints)
    : m_win_handle {nullptr}, m_ready_flag {true} {
        const auto [gl_major, gl_minor, gl_swap_interval] = gl_ctx_hints;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_win_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!m_win_handle) {
            m_ready_flag = false;
            std::cerr << "Failed to create window.\n";
            return;
        }

        glfwMakeContextCurrent(m_win_handle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            m_ready_flag = false;
            std::cerr << "Failed to load OpenGL bindings by GLAD.\n";
            return;
        }

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(m_win_handle, handleWindowResize);
        glfwSwapInterval(swap_interval); // for vsync
    }

    Window::~Window() {
        glfwTerminate();
    }

    bool Window::isReady() const { return m_ready_flag; }

    void Window::displayScene(Renderer& renderer) {
        /// @note Guard clause here must trigger when the GL program build failed earlier, so I cannot draw well if that case applies.
        if (!renderer.isReady()) {
            return;
        }

        while (!glfwWindowShouldClose(m_win_handle)) {
            /// TODO: add processInput() method!

            renderer.renderBackground();
            renderer.renderThing();

            glfwPollEvents();
            glfwSwapBuffers(m_win_handle);
        }
    }
}