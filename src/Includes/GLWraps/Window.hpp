#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "AppCtrl/KeyData.hpp"
#include "Game/Game.hpp"
#include "GLFW3/glfw3.h"

namespace GLProject1::GLWraps {
    struct WindowGLConfig {
        int major_version;
        int minor_version;
        int swap_interval;
    };

    class Window;

    /**
     * @brief Contains reference pointers to Game & Window states for callback function usage.
     */
    class ServiceRefs {
    public:
        explicit ServiceRefs(Game::Game* game_state_ptr, Window* window_ptr) noexcept;
        [[nodiscard]] Game::Game* refGameState() noexcept;
        [[nodiscard]] Window* refWindow() noexcept;
        explicit operator bool() const noexcept;

    private:
        Game::Game* m_game_state_ptr;
        Window* m_window_ptr;
        bool m_ready;
    };

    class Window {
    public:
        using keycode_t = AppCtrl::KeyCode;
        using resize_func_t = void(GLFWwindow*, int, int);
        using resize_func_ptr = resize_func_t*;
        using key_func_t = void(GLFWwindow*, int, int, int, int);
        using key_func_ptr = key_func_t*;

        Window() noexcept;
        Window(const char* title, int width, int height, WindowGLConfig gl_ctx_hints);

        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        [[nodiscard]] bool isReady() const;

        void setViewingDims(int width, int height) noexcept;

        void displayGame(Game::Game& game_state);

        [[nodiscard]] bool setResizeCallback(resize_func_ptr on_resize) noexcept;
        [[nodiscard]] bool setKeyCallback(key_func_ptr on_key) noexcept;

    private:
        GLFWwindow* m_win_handle;
        int m_window_width;
        int m_window_height;
        bool m_ready_flag;
        bool m_running;
    };
}

#endif