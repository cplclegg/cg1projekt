#version 330 core
layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNorm;

out vec3 fragNorm;

uniform mat4 transform;

void main() {
    fragNorm = vertNorm;
    gl_Position = transform * vec4(vertPosition, 1.0);
}