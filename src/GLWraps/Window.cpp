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
    : m_win_handle {nullptr}, m_current_key {}, m_ready_flag {false}, m_running {false} {}

    Window::Window(const char* title, int width, int height, WindowGLConfig gl_ctx_hints)
    : m_win_handle {nullptr}, m_current_key {}, m_ready_flag {true}, m_running {false} {
        const auto [gl_major, gl_minor, gl_swap_interval] = gl_ctx_hints;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

        glfwSetFramebufferSizeCallback(m_win_handle, handleWindowResize);
        glfwSwapInterval(gl_swap_interval); // for vsync

        glfwGetFramebufferSize(m_win_handle, &width, &height);
        glViewport(0, 0, width, height);
    }

    Window::~Window() {
        glfwTerminate();
    }

    bool Window::isReady() const { return m_ready_flag; }

    void Window::displayGame(Game::Game& game_state) {
        /// @note Guard clause here must trigger when the GL program build failed earlier, so I cannot draw well if that case applies.
        if (!isReady() || m_running) {
            return;
        }

        m_running = true;
        auto game_won = false;

        while (!glfwWindowShouldClose(m_win_handle) && !game_won) {
            /// NOTE: gets user's keyboard inputs to move their player...
            processInput();

            int current_win_width = 0;
            int current_win_height = 0;
            glfwGetFramebufferSize(m_win_handle, &current_win_width, &current_win_height);

            game_won = game_state.processInput(m_current_key, static_cast<float>(current_win_width), static_cast<float>(current_win_height));

            glfwPollEvents();
            glfwSwapBuffers(m_win_handle);
        }
    }

    void Window::processInput() {
        if (glfwGetKey(m_win_handle, GLFW_KEY_UP) == GLFW_PRESS) {
            m_current_key = keycode_t::key_arrow_up;
        } else if (glfwGetKey(m_win_handle, GLFW_KEY_DOWN) == GLFW_PRESS) {
            m_current_key = keycode_t::key_arrow_down;
        } else if (glfwGetKey(m_win_handle, GLFW_KEY_LEFT)) {
            m_current_key = keycode_t::key_arrow_left;
        } else if (glfwGetKey(m_win_handle, GLFW_KEY_RIGHT)) {
            m_current_key = keycode_t::key_arrow_right;
        } else {
            m_current_key = keycode_t::key_unknown;
        }
    }
}