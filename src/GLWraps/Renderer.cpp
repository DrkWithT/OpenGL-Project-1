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

#include "GLWraps/Renderer.hpp"

namespace GLProject1::GLWraps {
    Scene makeScene(std::initializer_list<Mesh> meshes, const ScaledRGBColor& bg) {
        std::vector<Mesh> temp_meshes = meshes;

        return {temp_meshes, bg};
    }


    Renderer::Renderer(Scene&& scene, Program&& program)
    : m_scene {scene}, m_program {program} {}

    bool Renderer::isReady() const { return m_program.isValid(); }

    void Renderer::renderScene() {
        const auto [bg_red, bg_green, bg_blue] = getSceneBackground();

        glClearColor(bg_red, bg_green, bg_blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_program.useSelf();

        for (const auto& mesh : getSceneObjects()) {
            mesh.getVAO().bindSelf();
            glDrawElements(GL_TRIANGLES, mesh.getVAO().getIndexCount(), GL_UNSIGNED_INT, 0);
            mesh.getVAO().unbindSelf();
        }
    }

    const std::vector<Mesh>& Renderer::getSceneObjects() const { return m_scene.objects; }

    const ScaledRGBColor& Renderer::getSceneBackground() const { return m_scene.background; }
}