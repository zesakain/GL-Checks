#version 330 core
layout (location = 0) in vec3 aPos; // Position attribute at index 0

// Uniforms are variables passed from C++ to GPU that stay constant for the whole mesh
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Matrix multiplication: Projection * View * Model * Position
    // This transforms 3D world coordinates to 2D screen space
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
