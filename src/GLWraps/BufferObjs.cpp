/**
 * @file BufferObjs.cpp
 * @author DrkWithT
 * @brief Implements RAII wrappers for VBO, VAO, and later EBOs.
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/BufferObjs.hpp"
#include "GLAD3/glad.h"

namespace GLProject1::GLWraps {
    static constexpr int point_dim = 3;


    VertexStore::VertexStore(std::initializer_list<PositionVertex> points)
    : m_data {std::make_unique<float[]>(3 * points.size())}, m_length {points.size()}, m_datasize {3 * sizeof(float) * points.size()} {
        int point_data_pos = 0;

        for (const auto [x, y, z] : points) {
            m_data[point_data_pos] = x;
            m_data[point_data_pos + 1] = y;
            m_data[point_data_pos + 2] = z;

            point_data_pos += point_dim;
        }
    }

    const float* VertexStore::viewData() const { return m_data.get(); }

    std::size_t VertexStore::getLength() const { return m_length; }

    std::size_t VertexStore::getDataSize() const { return m_datasize; }


    glw_handle_t makeBufferHandle() {
        glw_handle_t result;

        glGenBuffers(1, &result);

        return result;
    }

    glw_handle_t makeVAOHandle() {
        glw_handle_t result;

        glGenVertexArrays(1, &result);

        return result;
    }


    VAO::VAO(const MeshData& data)
    : m_handle {makeVAOHandle()}, m_vbo_handle {makeBufferHandle()}, m_ebo_handle {makeBufferHandle()}, m_ebo_index_n {0} {
        const auto& [vertex_data, index_data] = data;

        glBindVertexArray(m_handle);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_handle);
        glBufferData(GL_ARRAY_BUFFER, vertex_data.getDataSize(), vertex_data.viewData(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glw_handle_t) * index_data.size(), index_data.data(), GL_STATIC_DRAW);
        m_ebo_index_n = static_cast<int>(index_data.size());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, point_dim * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

    glw_handle_t VAO::getHandle() const {
        return m_handle;
    }

    int VAO::getIndexCount() const { return m_ebo_index_n; }

    void VAO::unbindSelf() & {
        glBindVertexArray(0);
    }

    void VAO::bindSelf() & {
        glBindVertexArray(m_handle);
    }

    void VAO::unbindSelf() const& {
        glBindVertexArray(0);
    }

    void VAO::bindSelf() const& {
        glBindVertexArray(m_handle);
    }
}