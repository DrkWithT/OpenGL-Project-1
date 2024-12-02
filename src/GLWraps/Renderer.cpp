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
    Renderer::Renderer(Program&& program, Mesh&& drawable, const RenderConfig& config)
    : m_program {program}, m_drawable {drawable}, m_bg_color {toScaledRGB(config.bg_color)} {}

    bool Renderer::isReady() const { return m_program.isValid(); }

    void Renderer::renderThing() {
        glClearColor(m_bg_color.r, m_bg_color.g, m_bg_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_program.useSelf();
        m_drawable.getVAO().bindSelf();
        glDrawElements(GL_TRIANGLES, m_drawable.getVAO().getIndexCount(), GL_UNSIGNED_INT, 0);

        m_drawable.getVAO().unbindSelf();
    }
}