#version 330 core
in vec3 fragNorm;
void main() {
    gl_FragColor = vec4(fragNorm, 1.0);
}