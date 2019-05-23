#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexcoord;

uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform mat4 modelInvTransMat;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertexPos, 1.0);
    FragPos = vec3(modelMat * vec4(vertexPos, 1.0));
    TexCoord = vertexTexcoord;

    Normal = vec3(modelInvTransMat * vec4(vertexNormal, 1.0));
}
