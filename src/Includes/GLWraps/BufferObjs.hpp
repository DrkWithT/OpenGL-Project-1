#ifndef BUFFER_OBJS_HPP
#define BUFFER_OBJS_HPP

#include <memory>
#include <initializer_list>
#include <vector>

#include "GLWraps/BasicTypes.hpp"

namespace GLProject1::GLWraps {
    class VertexStore {
    public:
        VertexStore() = delete;
        VertexStore(std::initializer_list<PositionVertex> points);

        const float* viewData() const;
        std::size_t getLength() const;
        std::size_t getDataSize() const;

    private:
        std::unique_ptr<float[]> m_data;
        std::size_t m_length;
        std::size_t m_datasize;
    };


    struct MeshData {
        VertexStore vertex_data;
        std::vector<glw_handle_t> index_data;
    };



    [[nodiscard]] glw_handle_t makeBufferHandle();
    [[nodiscard]] glw_handle_t makeVAOHandle();


    /// @note Contains a VAO with an internal VBO handle too.
    class VAO {
    public:
        VAO() = delete;
        VAO(const MeshData& data);

        [[nodiscard]] glw_handle_t getHandle() const;
        [[nodiscard]] int getIndexCount() const;

        void unbindSelf() &;
        void bindSelf() &;
        void unbindSelf() const&;
        void bindSelf() const&;

    private:
        glw_handle_t m_handle;
        glw_handle_t m_vbo_handle;
        glw_handle_t m_ebo_handle;
        int m_ebo_index_n;
    };
}

#endif