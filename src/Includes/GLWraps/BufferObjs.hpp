#ifndef BUFFER_OBJS_HPP
#define BUFFER_OBJS_HPP

#include <memory>
#include <initializer_list>

namespace GLProject1::GLWraps {
    using buf_handle_t = unsigned int;

    struct PositionVertex {
        float x;
        float y;
        float z;
    };

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

    [[nodiscard]] buf_handle_t makeVBOHandle();
    [[nodiscard]] buf_handle_t makeVAOHandle();

    /// @note Contains a VAO with an internal VBO handle too.
    class VAO {
    public:
        VAO() = delete;
        VAO(const VertexStore& data);

        [[nodiscard]] buf_handle_t getHandle() const;
        void unbindSelf();
        void bindSelf();

    private:
        buf_handle_t m_handle;
        buf_handle_t m_vbo_handle;
    };
}

#endif