#ifndef SHADER_UTILS_HPP
#define SHADER_UTILS_HPP

#include <format>
#include <iostream>
#include "GLAD3/glad.h"
#include "GLWraps/BasicTypes.hpp"

namespace GLProject1::GLWraps {
    enum class ShaderType {
        vertex,
        geometry,
        fragment
    };

    template <ShaderType T>
    struct shadertype_to_glcode {};

    template <>
    struct shadertype_to_glcode <ShaderType::vertex> {
        static constexpr int code = GL_VERTEX_SHADER;
    };

    template <>
    struct shadertype_to_glcode <ShaderType::geometry> {
        static constexpr int code = GL_GEOMETRY_SHADER;
    };

    template <>
    struct shadertype_to_glcode <ShaderType::fragment> {
        static constexpr int code = GL_FRAGMENT_SHADER;
    };

    template <ShaderType T>
    class Shader {
    private:
        glw_handle_t m_handle;
        bool m_valid_flag;

    public:
        Shader() = delete;
        Shader(const char* src_embed)
        : m_handle {glCreateShader(shadertype_to_glcode<T>::code)}, m_valid_flag {true} {
            glShaderSource(m_handle, 1, &src_embed, nullptr);
            glCompileShader(m_handle);

            int compile_ok = 0;
            char compile_log[256];
            glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compile_ok);

            if (!compile_ok) {
                glGetShaderInfoLog(m_handle, 256, nullptr, compile_log);
                std::cerr << std::format("Error [shader compile]: \"{}\"\n", compile_log);
                m_valid_flag = false;
            }
        }

        ~Shader() {
            glDeleteShader(m_handle);
        }

        [[nodiscard]] glw_handle_t getHandle() const { return m_handle; }

        [[nodiscard]] bool isValid() const { return m_valid_flag; }
    };

    using VertexShader = Shader<ShaderType::vertex>;
    using GeometryShader = Shader<ShaderType::geometry>;
    using FragmentShader = Shader<ShaderType::fragment>;

    class Program {
    private:
        glw_handle_t m_handle;
        bool m_valid_flag;

        /// @note Default Program is an unusable dud in case Shaders fail to build!
        Program();
        Program(glw_handle_t vtx_shader, glw_handle_t frg_shader);
        Program(glw_handle_t vtx_shader, glw_handle_t geo_shader, glw_handle_t frg_shader);

    public:
        [[nodiscard]] glw_handle_t getHandle() const;
        [[nodiscard]] bool isValid() const;
        void useSelf();

        [[nodiscard]] static Program makeProgram(const char* vtx_shader_src, const char* frag_shader_src);
        [[nodiscard]] static Program makeProgram(const char* vtx_shader_src, const char* geo_shader_src, const char* frag_shader_src);
    };

}

#endif