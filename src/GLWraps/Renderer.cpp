/**
 * @file Renderer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/BasicTypes.hpp"
#include "GLWraps/Uniform.hpp"
#include "GLWraps/Renderer.hpp"

namespace GLProject1::GLWraps {
    Scene makeScene(std::initializer_list<Mesh> meshes, const ScaledRGBColor& bg) {
        std::vector<Mesh> temp_meshes = meshes;

        return {temp_meshes, bg};
    }


    Renderer::Renderer(Scene&& scene, Program&& program, const char* stencil_uniform_name)
    : m_scene {scene}, m_program {program}, m_fixed_stencil_name {stencil_uniform_name} {}

    bool Renderer::isReady() const { return m_program.isValid(); }

    void Renderer::renderScene() {
        const auto [bg_red, bg_green, bg_blue] = getSceneBackground();

        glClearColor(bg_red, bg_green, bg_blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (const auto& mesh : getSceneObjects()) {
            const glw_uniform_handle_t updated_uniform = glGetUniformLocation(m_program.getHandle(), m_fixed_stencil_name);

            m_program.useSelf();

            updateMeshStencil(updated_uniform, mesh.getColor());

            mesh.getVAO().bindSelf();
            glDrawElements(GL_TRIANGLES, mesh.getVAO().getIndexCount(), GL_UNSIGNED_INT, 0);
            mesh.getVAO().unbindSelf();
        }
    }

    const std::vector<Mesh>& Renderer::getSceneObjects() const { return m_scene.objects; }

    const ScaledRGBColor& Renderer::getSceneBackground() const { return m_scene.background; }

    void Renderer::updateMeshStencil(glw_uniform_handle_t uniform_handle, const ScaledRGBColor& color) {
        const auto [red, green, blue] = color;

        RGBUniform::updateData(uniform_handle, red, green, blue);
    }
}