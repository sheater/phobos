#version 330 core

#define MAX_LIGHTS 24

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Light {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 position;
};

layout (std140) uniform lightData {
    int numLights;
    Light lights[MAX_LIGHTS];
};

uniform mat4 viewMat;
uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform vec4 materialSpecularColor; // kinda ambient in this lighting model
uniform sampler2D ourTexture;
uniform float opacity;

void main()
{
    vec3 colorSum = vec3(0);
    vec3 norm = normalize(Normal);

    for (int i = 0; i < numLights; i++)
    {
        vec3 lightDir = normalize(lights[i].position.xyz - FragPos);
        float cosTheta = max(dot(norm, lightDir), 0.0);

        vec3 ambientColor = materialAmbientColor.rgb * lights[i].ambientColor.rgb;
        vec3 diffuseColor = cosTheta * materialDiffuseColor.rgb * lights[i].diffuseColor.rgb;
        vec3 specularColor = materialSpecularColor.rgb * lights[i].specularColor.rgb;

        colorSum += ambientColor + diffuseColor; //+ specularColor;
    }

    FragColor = vec4(colorSum, opacity);
}
