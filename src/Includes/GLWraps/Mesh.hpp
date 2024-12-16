#ifndef MESH_HPP
#define MESH_HPP

#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/BufferObjs.hpp"
#include "GLM/glm/vec3.hpp"

namespace GLProject1::GLWraps {
    class Mesh {
    public:
        Mesh() = delete;
        Mesh(const MeshData& data, const GLWraps::ScaledRGBColor& color);

        const VAO& getVAO() const;

        const ScaledRGBColor& getColor() const;

        const glm::vec3& getTranslation() const;

        void moveUp();

        void moveDown();

    private:
        VAO m_draw_data;
        glm::vec3 m_pos_translate;
        ScaledRGBColor m_color;
    };
}

#endif