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

uniform structMaterial {// параметры материала
        sampler2D texture;
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        vec4 emission;
        float shininess;
} material;

// параметры полученные из вершинного шейдера
in Vertex {
        vec2 texcoord;
        vec3 normal;
        vec3 lightDir;
        vec3 viewDir;
        float distance;
} Vert;

void main ( void ){
    //нормализаци€ полученных данных
    //дл€ коррекции интерпол€ции
    vec3 normal = normalize(Vert.normal);
    vec3 lightDir = normalize(Vert.lightDir);
    vec3 viewDir = normalize(Vert.viewDir);

    //вычисление коэффициента затухани€
    float attenuation = 1.0 / (light.attenuation[0] +
            light.attenuation[1] * Vert.distance +
            light.attenuation[2] * Vert.distance * Vert.distance);

    //добавление собственного свечени€ материала
    color = material.emission;
    //добавление фоновое освещение
    color += material.ambient * light.ambient * attenuation;
    //добавление рассе€нного света
    float Ndot = max(dot(normal, lightDir), 0.0);
    color += material.diffuse * light.diffuse * Ndot * attenuation;
    //добавление отраженного света
    float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);
    color += material.specular * light.specular * RdotVpow * attenuation;

    //или
    //вычисление итогового цвета пиксел€ с учЄтом собственного цвета
    //color *= color_obj;
    //или
    // вычислим итоговый цвет пиксел€ на экране с учЄтом текстуры
    color *= texture(material.texture, Vert.texcoord);
}
