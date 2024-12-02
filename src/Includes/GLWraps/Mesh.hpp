#ifndef MESH_HPP
#define MESH_HPP

#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/BufferObjs.hpp"

namespace GLProject1::GLWraps {
    class Mesh {
    public:
        Mesh() = delete;
        Mesh(const MeshData& data, const GLWraps::ScaledRGBColor& color);

        const VAO& getVAO() const;
        const ScaledRGBColor& getColor() const;

    private:
        VAO m_draw_data;
        ScaledRGBColor m_color;
    };
}

#endif