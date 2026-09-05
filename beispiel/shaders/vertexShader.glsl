#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;

uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProj;
uniform mat3 mNormal;

out vec2 textureCoord;
out vec3 fNormal;
out vec3 FragPos;
void main() {
    FragPos = vec3(mWorld * vec4(vPosition, 1.0));
    textureCoord = vTexCoord;
    fNormal = transpose(inverse(mat3(mWorld))) * vNormal;
    //fNormal = mNormal * vNormal;
    gl_Position = mProj * mView * mWorld * vec4(vPosition, 1.0);
}
