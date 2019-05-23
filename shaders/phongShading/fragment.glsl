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
uniform vec4 materialSpecularColor;
uniform sampler2D ourTexture;
uniform float opacity;

const vec3 cameraPosition = vec3(0.0f);

void main()
{
    vec3 colorSum = vec3(0);
    vec3 norm = normalize(Normal);

    for (int i = 0; i < numLights; i++)
    {
        Light light = lights[i];
        vec3 light_vector = light.position.xyz - FragPos; //* light.position.w;
		vec3 L = normalize(light_vector);
		vec3 N = norm;
		vec3 E = -normalize(cameraPosition - FragPos); 
		vec3 H = normalize(L + E);

		float NdotL = max(dot(N, L), 0.0); // for diffuse
		float NdotH = max(dot(N, H), 0.000001); // for specular

		float distance2 = light.position.w == 1.0 ? pow(length(light_vector), 2) : 1.0;

		vec3 ambient = materialAmbientColor.rgb * light.ambientColor.rgb;
		vec3 diffuse = materialDiffuseColor.rgb * light.diffuseColor.rgb;
		vec3 specular = materialSpecularColor.rgb * light.specularColor.rgb;

		vec3 color = ambient.rgb
			+ NdotL * diffuse.rgb;
			+ pow(NdotH, materialSpecularColor.w) * specular;
		color /= distance2;

		colorSum += color;
    }

    FragColor = vec4(colorSum, opacity);
}
