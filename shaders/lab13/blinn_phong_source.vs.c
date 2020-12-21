#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 normal;

uniform struct Transform {
	mat4 model;
	mat4 viewProjection;
	mat3 normal;
	vec3 viewPosition;
} transform;

uniform struct PointLight {
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 attenuation;
} light;

out Vertex {
	vec2 texcoord;
	vec3 normal;
	vec3 lightDir;
	vec3 viewDir;
	float distance;
} Vert;

varying vec4 l;
varying vec3 n;

void main() {
	vec4 vertex   = transform.model * vec4(position, 1.0);
	vec4 lightDir = light.position - vertex;
	l = normalize(lightDir);
	n = normalize(transform.normal * normal);
	Vert.texcoord = texcoord;
	Vert.normal   = transform.normal * normal;
	Vert.lightDir = vec3(light.position);
	Vert.viewDir  = transform.viewPosition - vec3(vertex);
	gl_Position = transform.viewProjection * vertex;
};