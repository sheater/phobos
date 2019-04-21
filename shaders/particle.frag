#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
uniform float opacity;
uniform sampler2D ourTexture;
uniform vec4 color;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * color * opacity;
}
