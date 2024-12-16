/**
 * @file Mesh.cpp
 * @author DrkWithT
 * @brief Implements Mesh wrapper.
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/Mesh.hpp"

namespace GLProject1::GLWraps {
    Mesh::Mesh(const MeshData& data, const GLWraps::ScaledRGBColor& color)
    : m_draw_data {data}, m_pos_translate {0.0f, 0.0f, 0.0f}, m_color {color} {}

    const VAO& Mesh::getVAO() const { return m_draw_data; }

    const ScaledRGBColor& Mesh::getColor() const { return m_color; }

    const glm::vec3& Mesh::getTranslation() const {
        return m_pos_translate;
    }

    void Mesh::moveUp() {
        m_pos_translate = {m_pos_translate.x, m_pos_translate.y + 0.0625f, m_pos_translate.z};
    }

    void Mesh::moveDown() {
        m_pos_translate = {m_pos_translate.x, m_pos_translate.y - 0.0625f, m_pos_translate.z};
    }
}