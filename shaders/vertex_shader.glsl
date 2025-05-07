#version 330 core

/// NOTE each point position in model comprises a fully Q4 square!
layout (location = 0) in vec3 aPos;

// converts from NDC to canvas-style coordinates (projection)
uniform mat4 originTransform;

// scales square of tile towards proportion to screen dimensions
uniform mat4 shrinkTransform;

// places same tile at position to board offset (model = placement * shrink)
uniform mat4 placeTransform;

void main() {
    gl_Position = originTransform * placeTransform * shrinkTransform * vec4(aPos.xy, 0.0f, 1.0f);
}