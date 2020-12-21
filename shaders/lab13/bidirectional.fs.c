out vec4 FragColor;

in Vertex {
        vec2 texcoord;
        vec3 normal;
        vec3 lightDir;
        vec3 viewDir;
        float distance;
} Vert;

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

void main(void) {
    const vec4 color0 = vec4(0.0, 0.0, 0.5, 1.0);
    const vec4 color2 = vec4(0.5, 0.5, 0.0, 1.0);

    vec3 n2 = normalize(n);
    vec3 l2 = normalize(vec3(l));
    vec4 diff = material.diffuse * color0 * max(dot(n2, l2), 0.0) + color2 * max(dot(n2, -l2), 0.0);

    FragColor = diff * texture(material.texture, Vert.texcoord);
}