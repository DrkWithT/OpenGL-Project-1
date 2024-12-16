#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <initializer_list>
#include <vector>
#include "AppCtrl/KeyData.hpp"
#include "GLWraps/BasicTypes.hpp"
#include "GLWraps/ColorUtils.hpp"
#include "GLWraps/Mesh.hpp"
#include "GLWraps/ShaderUtils.hpp"

namespace GLProject1::GLWraps {
    using MyKey = AppCtrl::KeyCode;

    /// NOTE: Stores a collection of objects to render, basically a "scene".
    struct Scene {
        std::vector<Mesh> objects;
        ScaledRGBColor background;
    };

    [[nodiscard]] Scene makeScene(std::initializer_list<Mesh> meshes, const ScaledRGBColor& bg);

    class Renderer {
    public:
        Renderer() = delete;
        Renderer(Scene&& scene, Program&& program, const char* stencil_uniform_name);
        Renderer(Scene&& scene, Program&& program, const char* stencil_uniform_name, const char* transform_uniform_name);

        bool isReady() const;
        void renderScene(MyKey key);

    private:
        Scene m_scene;
        Program m_program;
        const char* m_fixed_stencil_name;
        const char* m_transform_name;

        std::vector<Mesh>& getSceneObjects();
        const ScaledRGBColor& getSceneBackground() const;
        void updateMeshStencil(glw_uniform_handle_t uniform_handle, const ScaledRGBColor& color);
        void updateMeshDisplacement(glw_uniform_handle_t uniform_handle, const float* transform_data);
    };
}

#endif