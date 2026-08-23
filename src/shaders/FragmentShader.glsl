#version 330 core
in vec2 text;
uniform sampler2D boxTexture;
void main() {
    gl_FragColor = texture2D(boxTexture, text);
}
