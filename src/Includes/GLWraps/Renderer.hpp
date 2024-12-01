#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/BufferObjs.hpp"
#include "GLWraps/ShaderUtils.hpp"

namespace GLProject1::GLWraps {
    struct RenderConfig {
        RGBColor bg_color;
    };

    class Renderer {
    public:
        Renderer() = delete;
        Renderer(Program&& program, VAO&& drawable, const RenderConfig& config);

        bool isReady() const;
        void renderBackground();
        void renderThing();

    private:
        Program m_program;

        /// TODO: replace with collection of drawables as a "Scene"!
        VAO m_drawable;

        /// TODO: refactor VAO & colors out into a "Drawable" later.
        ScaledRGBColor m_bg_color;
    };
}

#endif