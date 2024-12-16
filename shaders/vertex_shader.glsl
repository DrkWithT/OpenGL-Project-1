#version 330 core

layout (location = 0) in vec3 aPos;
uniform mat4 dTransform;

void main() {
    gl_Position = dTransform * vec4(aPos, 1.0f);
}