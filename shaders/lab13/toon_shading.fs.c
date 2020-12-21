#version 330 core

out vec4 FragColor;

in Vertex {
    vec2 texcoord;
    vec3 normal;
    vec3 lightDir;
    vec3 viewDir;
    float distance;
} Vert;

uniform struct PointLight {
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 attenuation;
} light;

uniform struct Material {
    sampler2D texture;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
} material;

varying vec4 l;
varying vec3 n;

void main() {
	vec3 n2 = normalize(n);
	vec3 l2 = normalize(vec3(l));
	float diff = 0.2 + max ( dot ( n2, l2 ), 0.0 );
	vec4 color;
	if (diff < 0.4)
		color = material.diffuse * 0.3;
	else
	if (diff < 0.7)
		color = material.diffuse;
	else
		color = material.diffuse * 1.3;
	FragColor = color * texture(material.texture, Vert.texcoord);
};