#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform sampler2D ourTexture;
uniform float opacity;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float cosTheta = max(dot(norm, lightDir), 0.0);
    vec4 diffuseColor = materialDiffuseColor * cosTheta * lightColor;

    FragColor = (materialAmbientColor + diffuseColor) * opacity;
}
