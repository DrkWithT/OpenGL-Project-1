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
    ServiceRefs::ServiceRefs(Game::Game* game_state_ptr, Window* window_ptr) noexcept
    : m_game_state_ptr {game_state_ptr}, m_window_ptr {window_ptr}, m_ready {m_game_state_ptr != nullptr && m_window_ptr != nullptr} {}

    Game::Game* ServiceRefs::refGameState() noexcept {
        return m_game_state_ptr;
    }

    Window* ServiceRefs::refWindow() noexcept {
        return m_window_ptr;
    }

    ServiceRefs::operator bool() const noexcept {
        return m_ready;
    }

    Window::Window() noexcept
    : m_win_handle {nullptr}, m_ready_flag {false}, m_running {false} {}

    Window::Window(const char* title, int width, int height, WindowGLConfig gl_ctx_hints)
    : m_win_handle {nullptr}, m_window_width {width}, m_window_height {height}, m_ready_flag {true}, m_running {false} {
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

        glfwSwapInterval(gl_swap_interval); // for vsync

        glfwGetFramebufferSize(m_win_handle, &width, &height);
        glViewport(0, 0, m_window_width, m_window_height);
    }

    Window::~Window() {
        glfwTerminate();
    }

    bool Window::isReady() const { return m_ready_flag; }

    void Window::setViewingDims(int width, int height) noexcept {
        m_window_width = width;
        m_window_height = height;
        glViewport(0, 0, m_window_width, m_window_height);
    }

    void Window::displayGame(Game::Game& game_state) {
        /// @note Guard clause here must trigger when the GL program build failed earlier, so I cannot draw well if that case applies.
        if (!isReady() || m_running) {
            return;
        }

        m_running = true;
        auto game_won = false;

        while (!glfwWindowShouldClose(m_win_handle) && !game_won) {
            game_state.display(static_cast<float>(m_window_width), static_cast<float>(m_window_height));
            game_won = game_state.isPassed();

            glfwPollEvents();
            glfwSwapBuffers(m_win_handle);
        }
    }

    bool Window::setResizeCallback(resize_func_ptr on_resize) noexcept {
        if (!m_win_handle || !on_resize) {
            return false;
        }

        glfwSetFramebufferSizeCallback(m_win_handle, on_resize);

        return true;
    }

    bool Window::setKeyCallback(key_func_ptr on_key) noexcept {
        if (!m_win_handle || !on_key) {
            return false;
        }

        glfwSetKeyCallback(m_win_handle, on_key);

        return true;
    }
}