/**
 * @file Renderer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/Renderer.hpp"

namespace GLProject1::GLWraps {
    Renderer::Renderer(Program&& program, VAO&& drawable, const RenderConfig& config)
    : m_program {program}, m_drawable {drawable}, m_bg_color {toScaledRGB(config.bg_color)} {}

    void Renderer::renderBackground() {
        const auto [bg_red, bg_green, bg_blue] = getPredefinedShade(ShadeOpt::gray);

        glClearColor(bg_red, bg_green, bg_blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::renderThing() {
        m_program.useSelf();
        m_drawable.bindSelf();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        m_drawable.unbindSelf();
    }
}