// #version 150 core
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
// out vec4 outColor;
uniform float opacity;
uniform sampler2D ourTexture;
uniform vec4 color;

void main()
{
    // outColor = vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = texture(ourTexture, TexCoord) * color * opacity;
}
