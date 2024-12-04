/**
 * @file BufferObjs.cpp
 * @author DrkWithT
 * @brief Implements my generalized Shader class & its helper functions.
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/ShaderUtils.hpp"

namespace GLProject1::GLWraps {
    static constexpr glw_handle_t dud_shader_id = 0;


    Program::Program()
    : m_handle {dud_shader_id}, m_valid_flag {false} {}

    Program::Program(glw_handle_t vtx_shader, glw_handle_t frg_shader)
    : m_handle {glCreateProgram()}, m_valid_flag {true} {
        glAttachShader(m_handle, vtx_shader);
        glAttachShader(m_handle, frg_shader);
        glLinkProgram(m_handle);

        int link_ok = 0;
        char link_log[256];
        glGetProgramiv(m_handle, GL_LINK_STATUS, &link_ok);

        if (!link_ok) {
            glGetShaderInfoLog(m_handle, 256, nullptr, link_log);
            std::cerr << std::format("Error [shader linking]: \"{}\"\n", link_log);
            m_valid_flag = false;
        }
    }

    Program::Program(glw_handle_t vtx_shader, glw_handle_t geo_shader, glw_handle_t frg_shader)
    : m_handle {glCreateProgram()}, m_valid_flag {true} {
        glAttachShader(m_handle, vtx_shader);
        glAttachShader(m_handle, geo_shader);
        glAttachShader(m_handle, frg_shader);
        glLinkProgram(m_handle);

        int link_ok = 0;
        char link_log[256];
        glGetProgramiv(m_handle, GL_LINK_STATUS, &link_ok);

        if (!link_ok) {
            glGetShaderInfoLog(m_handle, 256, nullptr, link_log);
            std::cerr << std::format("Error [shader linking]: \"{}\"\n", link_log);
            m_valid_flag = false;
        }
    }

    glw_handle_t Program::getHandle() const { return m_handle; }

    bool Program::isValid() const { return m_valid_flag; }

    void Program::useSelf() { glUseProgram(m_handle); }

    Program Program::makeProgram(const char* vtx_shader_src, const char* frag_shader_src) {
        VertexShader vshader {vtx_shader_src};
        FragmentShader fshader {frag_shader_src};

        if (!vshader.isValid() || !fshader.isValid()) {
            return {};
        }

        return {vshader.getHandle(), fshader.getHandle()};
    }

    Program Program::makeProgram(const char* vtx_shader_src, const char* geo_shader_src, const char* frag_shader_src) {
        VertexShader vshader {vtx_shader_src};
        GeometryShader gshader {geo_shader_src};
        FragmentShader fshader {frag_shader_src};

        if (!vshader.isValid() || !gshader.isValid() || !fshader.isValid()) {
            return {};
        }

        return {vshader.getHandle(), gshader.getHandle(), fshader.getHandle()};
    }
}