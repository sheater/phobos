#version 330 core

layout (location = 0) in vec3 particlePos;
layout (location = 1) in vec2 particleTexcoord;

uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

out vec2 TexCoord;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(particlePos, 1.0);
    TexCoord = particleTexcoord;
}
