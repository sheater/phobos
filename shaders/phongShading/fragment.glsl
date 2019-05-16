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

layout (std140) uniform lightData {
    int numLights;
    Light lights[MAX_LIGHTS];
};

uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform sampler2D ourTexture;
uniform float opacity;

void main()
{
    vec4 lightsColor = vec4(0);

    for (int i = 0; i < numLights; i++)
    {
        vec3 norm = normalize(Normal);
        vec3 distVec = lights[i].position - FragPos;
        vec3 lightDir = normalize(distVec);

        float cosTheta = max(dot(norm, lightDir), 0.0);

        lightsColor += cosTheta * lights[i].color;
    }

    vec4 diffuseColor = materialDiffuseColor * lightsColor;

    FragColor = (materialAmbientColor + diffuseColor) * opacity;
}
