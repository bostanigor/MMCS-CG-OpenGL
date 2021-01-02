#version 330 core

#define FRAG_OUTPUT0 0

layout (location = FRAG_OUTPUT0) out vec4 color;

uniform struct PointLight {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 attenuation;
} light;

uniform struct Material {
    sampler2D texture;
    sampler2D texture2;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emission;
    float shininess;
} material;

in Vertex {
        vec2 texcoord;
        vec3 normal;
        vec3 lightDir;
        vec3 viewDir;
        vec3 position;
        float distance;
} Vert;

uniform vec3 ourColor;
uniform float mixColor;
uniform float mixTexture;

void main(void) {
    vec3 normal = normalize(Vert.normal);
    vec3 lightDir = normalize(vec3(light.position) - Vert.position);
    vec3 viewDir = normalize(Vert.viewDir);

    float attenuation = 1.0 / (light.attenuation[0] +
                               light.attenuation[1] * Vert.distance +
                               light.attenuation[2] * Vert.distance * Vert.distance);

    color = material.emission;
    color += material.ambient * light.ambient * attenuation;
    float Ndot = max(dot(normal, lightDir), 0.0);
    color += material.diffuse * light.diffuse * Ndot * attenuation;
    float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);
    color += material.specular * light.specular * RdotVpow * attenuation;

    color *= mix(mix(texture(material.texture, Vert.texcoord), texture(material.texture2, Vert.texcoord), mixTexture), vec4(ourColor, 1.0), mixColor);
}