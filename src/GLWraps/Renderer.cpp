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

#include "GLM/glm/gtc/type_ptr.hpp"

namespace GLProject1::GLWraps {
    Scene makeScene(std::initializer_list<Mesh> meshes, const ScaledRGBColor& bg) {
        std::vector<Mesh> temp_meshes = meshes;

        return {temp_meshes, bg};
    }


    Renderer::Renderer(Scene&& scene, Program&& program, const char* stencil_uniform_name)
    : m_scene {scene}, m_program {program}, m_fixed_stencil_name {stencil_uniform_name} {}

    Renderer::Renderer(Scene&& scene, Program&& program, const char* stencil_uniform_name, const char* transform_uniform_name)
    : m_scene {scene}, m_program {program}, m_fixed_stencil_name {stencil_uniform_name}, m_transform_name {transform_uniform_name} {}

    bool Renderer::isReady() const { return m_program.isValid(); }

    void Renderer::renderScene(MyKey key) {
        const auto [bg_red, bg_green, bg_blue] = getSceneBackground();

        glClearColor(bg_red, bg_green, bg_blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // for (const auto& mesh : getSceneObjects()) {
        auto& one_mesh = getSceneObjects()[0];

        const glw_uniform_handle_t updated_stencil = glGetUniformLocation(m_program.getHandle(), m_fixed_stencil_name);
        const glw_uniform_handle_t updated_displace = glGetUniformLocation(m_program.getHandle(), m_transform_name);

        m_program.useSelf();

        updateMeshStencil(updated_stencil, one_mesh.getColor());

        glm::mat4 mesh_transform {1.0f};

        if (key == MyKey::key_arrow_up) {
            one_mesh.moveUp();
        } else if (key == MyKey::key_arrow_down) {
            one_mesh.moveDown();
        }

        mesh_transform = glm::translate(mesh_transform, one_mesh.getTranslation());

        updateMeshDisplacement(updated_displace, glm::value_ptr(mesh_transform));

        one_mesh.getVAO().bindSelf();
        glDrawElements(GL_TRIANGLES, one_mesh.getVAO().getIndexCount(), GL_UNSIGNED_INT, 0);
        one_mesh.getVAO().unbindSelf();
        // }
    }

    std::vector<Mesh>& Renderer::getSceneObjects() { return m_scene.objects; }

    const ScaledRGBColor& Renderer::getSceneBackground() const { return m_scene.background; }

    void Renderer::updateMeshStencil(glw_uniform_handle_t uniform_handle, const ScaledRGBColor& color) {
        const auto [red, green, blue] = color;

        RGBUniform::updateData(uniform_handle, red, green, blue);
    }

    void Renderer::updateMeshDisplacement(glw_uniform_handle_t uniform_handle, const float* transform_data) {
        T44Uniform::updateData(uniform_handle, transform_data);
    }
}