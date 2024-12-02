#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/Mesh.hpp"
#include "GLWraps/ShaderUtils.hpp"

namespace GLProject1::GLWraps {
    /// NOTE: This could be later repurposed into a Scene type.
    struct RenderConfig {
        RGBColor bg_color;
    };

    class Renderer {
    public:
        Renderer() = delete;
        Renderer(Program&& program, Mesh&& drawable, const RenderConfig& config);

        bool isReady() const;
        void renderBackground();
        void renderThing();

    private:
        Program m_program;

        /// TODO: create a Scene type storing Meshes and background color data.
        Mesh m_drawable;

        ScaledRGBColor m_bg_color;
    };
}

#endif