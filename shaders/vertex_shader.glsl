#version 330 core

/// NOTE each point position in model comprises a fully Q4 square!
layout (location = 0) in vec3 aPos;

// shrinks dims. to tile size
uniform float shrinkWidthFactor;
uniform float shrinkHeightFactor;

// places tile at equivalent position to board offset
uniform mat4 placeTransform;

void main() {
    const mat4 originTransform = mat4(
        1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    const mat4 shrinkTransform = mat4(
        1.0f / shrinkWidthFactor, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f / shrinkHeightFactor, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    gl_Position = placeTransform * shrinkTransform * originTransform * vec4(aPos, 1.0f);
}