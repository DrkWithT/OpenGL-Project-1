/**
 * @file Main.cpp
 * @author DrkWithT
 * @brief Implements main rendering logic.
 * @version 0.0.1
 * @date 2024-08-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

static constexpr int window_width = 480;
static constexpr int window_height = 480;

void on_window_resize([[maybe_unused]] GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // initialize GLFW ctx with OpenGL version hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // setup window
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Sample3", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    // bind OpenGL context to GLFW window for drawing within
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        return -1;
    }

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, on_window_resize); // for handling draws on resize
    glfwSwapInterval(1); // for vsync

    while (!glfwWindowShouldClose(window))
    {
        /// TODO: implement processInput(), see OpenGL book

        // show whitesmoke background
        glClearColor(0.925f, 0.925f, 0.925f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // process events if any
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
}