#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 texture;

uniform mat4 modelView;
uniform mat4 projM;

out vec2 text;

void main() {
	text = texture;
	gl_Position = projM * modelView * vec4(aPosition, 1.0);
}
