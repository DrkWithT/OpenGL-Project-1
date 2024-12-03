#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <initializer_list>
#include <vector>
#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/Mesh.hpp"
#include "GLWraps/ShaderUtils.hpp"

namespace GLProject1::GLWraps {
    /// NOTE: This could be later repurposed into a Scene type.
    struct RenderConfig {
        RGBColor bg_color;
    };

    /// NOTE: Stores a collection of objects to render, basically a "scene".
    struct Scene {
        std::vector<Mesh> objects;
        ScaledRGBColor background;
    };

    [[nodiscard]] Scene makeScene(std::initializer_list<Mesh> meshes, const ScaledRGBColor& bg);

    class Renderer {
    public:
        Renderer() = delete;
        Renderer(Scene&& scene, Program&& program);

        bool isReady() const;
        void renderScene();

    private:
        Scene m_scene;
        Program m_program;

        const std::vector<Mesh>& getSceneObjects() const;
        const ScaledRGBColor& getSceneBackground() const;
    };
}

#endif