#version 330 core

#define MAX_LIGHTS 24

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Light {
    vec4 color;
    vec3 position;
};

layout (std140) uniform lightData
{ 
    int numLights;
    Light lights[MAX_LIGHTS];
};

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform sampler2D ourTexture;
uniform float opacity;

// FIXME: currently broken
void main()
{
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos);

    // float cosTheta = max(dot(norm, lightDir), 0.0);
    // vec4 diffuseColor = materialDiffuseColor * cosTheta * lightColor;
    vec4 diffuseColor = vec4(1.0);

    FragColor = (materialAmbientColor + diffuseColor) * opacity;
}
