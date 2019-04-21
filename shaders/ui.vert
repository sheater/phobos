#version 330 core

layout (location = 0) in vec2 vertPos;
layout (location = 1) in vec2 vertTexcoord;

uniform mat4 projectionMat;
uniform vec2 position;
uniform vec2 size;

out vec2 TexCoord;

void main()
{
    gl_Position = projectionMat * vec4(position + vertPos * size, 0.0f, 1.0);
    TexCoord = vertTexcoord;
}
