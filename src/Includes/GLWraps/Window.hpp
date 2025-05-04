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

    void handleWindowResize([[maybe_unused]] GLFWwindow* raw_window, int new_width, int new_height);

    class Window {
    public:
        using keycode_t = AppCtrl::KeyCode;

        Window() noexcept;
        Window(const char* title, int width, int height, WindowGLConfig gl_ctx_hints);

        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        [[nodiscard]] bool isReady() const;

        void displayGame(Game::Game& game_state);

    private:
        GLFWwindow* m_win_handle;
        keycode_t m_current_key;
        bool m_ready_flag;
        bool m_running;

        /// NOTE: use a background thread at startup to belatedly timeout the key debounce for each submitted key-press...
        void processInput();
    };
}

#endif