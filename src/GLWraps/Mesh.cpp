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
    : m_draw_data {data}, m_color {color} {}

    const VAO& Mesh::getVAO() const { return m_draw_data; }

    const ScaledRGBColor& Mesh::getColor() const { return m_color; }
}