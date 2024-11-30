#ifndef WINDOW_HPP
#define WINDOW_HPP

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
        Window() noexcept;
        Window(const char* title, int width, int height, int swap_interval, WindowGLConfig gl_ctx_hints);

        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        [[nodiscard]] bool isReady() const;

        void displayScene();

        // void displayScene(Renderer& renderer);

    private:
        GLFWwindow* m_win_handle;
        bool m_ready_flag;
    };
}

#endif