#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 texture;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projM;

out vec2 text;

void main() {
	text = texture;
	gl_Position = projM * viewM * modelM * vec4(aPosition, 1.0);
}
