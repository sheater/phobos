#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;

uniform vec4 materialDiffuseColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = materialDiffuseColor;
}
