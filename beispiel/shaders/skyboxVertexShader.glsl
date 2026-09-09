#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 mProjection;
uniform mat4 mView;

void main()
{
    TexCoords = aPos;
    vec4 pos = mProjection * mView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
