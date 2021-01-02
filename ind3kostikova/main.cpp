#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "../common/model3D.h"
#include "../common/sceneObject.h"
#include <cmath>
#include <iostream>

#define PI 3.1415

GLuint shader;

int width, height;
GLfloat angleY = 0.0f;
GLfloat cameraDistance = 3.0f;

mat4 cameraMatrix;
std::vector<sceneObject> sceneObjects;

UniformStruct uniformLight;
UniformStruct uniformMaterial;
UniformStruct uniformTransform;

vec3 uniformColor = vec3{0.0, 0.0, 1.0};
GLuint texture2;
float mixColor;
float mixTexture;

Light light = Light({ 8.0, 3.0f, 0.0, 1.0 },
                    { 0.5, 0.5, 0.5, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0 });

Material * material;
Transform * transform = new Transform {
        {}, {},

        {1.0, 0.0, 0.0,
         0.0, 1.0, 0.0,
         0.0, 0.0, 1.0},

        { 0.0, 0.0, 0.0f}
};


void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    light.setUniform(shader, uniformLight);


    for (auto object : sceneObjects) {
        material = &(object.material);
        transform->model = object.getModelTransform() * cameraMatrix;

        material->setUniform(shader, uniformMaterial, texture2);
        transform->setUniform(shader, uniformTransform);


        object.render();
    }

    glFlush();
    glutSwapBuffers();
}

void update() {
    angleY += 0.001f;
    vec3 cameraPos = {
            cameraDistance * sin(angleY),
            1.2,
            cameraDistance * cos(angleY)
    };
    transform->viewPosition = cameraPos;

    glUniform3f(getUniformId("ourColor", shader), uniformColor.x, uniformColor.y, uniformColor.z);
    glUniform1f(getUniformId("mixColor", shader), mixColor);
    glUniform1f(getUniformId("mixTexture", shader), mixTexture);

    cameraMatrix = offsetMatrix(-cameraPos) * rotationYMatrix(angleY);
    render();
}

void setPerspective(float fov, float aspectRatio, float nearf, float farf) {
    float f = 1.0f / tan(fov * PI / 360);
    transform->viewProjection = {
            f / aspectRatio, 0.0f, 0.0f, 0.0f,
            0.0f, f, 0.0f, 0.0f,
            0.0f, 0.0f, (farf + nearf) / (nearf - farf), -1.0f,
            0.0f, 0.0f, (2 * farf * nearf) / (nearf - farf), 0.0
    };
}

void resizeWindow(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    setPerspective(90.0f, (float)width / height, 1.0f, 1500000.0f);
}

void freeShaders() {
    glDeleteProgram(shader);
}

void initShader() {
    shader = initShaderProgram("../shaders/ind_shader.vs.c",
                               "../shaders/ind_shader.fs.c");
    glUseProgram(shader);
    uniformLight = UniformStruct("light", {
            "position",
            "ambient",
            "diffuse",
            "specular",
            "attenuation",
    }, {shader});
    uniformMaterial = UniformStruct("material", {
            "texture",
            "ambient",
            "diffuse",
            "specular",
            "emission",
            "shininess",
    }, {shader});
    uniformTransform = UniformStruct("transform", {
            "model",
            "viewProjection",
            "normal",
            "viewPosition"
    }, {shader});
    uniformColor = vec3{0.0, 0.0, 1.0};
    texture2 = loadTex("../assets/glitter.jpg");
}

void initScene() {
    auto table_model = new model3D("../assets/models/table/table.obj", (float)(1.0f / 1.5f));
    auto table_texture = loadTex("../assets/models/table/wood.jpg");
    Material material = {table_texture,
                         { 1.0f, 1.0f, 1.0f, 1.0f },
                         { 1.0f, 1.0f, 1.0f, 1.0f },
                         { 1.0f, 1.0f, 1.0f, 1.0f },
                         { 0, 0, 0 },
                         32.0f };
    sceneObjects.emplace_back(table_model, material, vec3{0.0, 0.0f, 0.0});

    auto chair = new model3D("../assets/models/chair.obj", (float)(1.0f / 70.0f));
    auto chair_texture = loadTex("../assets/leather.jpg");
    Material chair_material = {chair_texture,
                               { 1.0f, 1.0f, 1.0f, 1.0f },
                               { 1.0f, 1.0f, 1.0f, 1.0f },
                               { 1.0f, 1.0f, 1.0f, 1.0f },
                         { 0, 0, 0 },
                         30.0f };
    sceneObjects.emplace_back(chair, chair_material, vec3{1.5, 0.0, 0.0});

    auto plant = new model3D("../assets/models/plant1/plant1.obj", (float)(1.0f / 5.0f));
    auto plant_texture = loadTex("../assets/models/plant1/plant1.jpg");
    Material plant_material = {plant_texture,
                               { 1.0f, 1.0f, 1.0f, 1.0f },
                               { 1.0f, 1.0f, 1.0f, 1.0f },
                               { 1.0f, 1.0f, 1.0f, 1.0f },
                               { 0, 0, 0 },
                               20.0f };
    sceneObjects.emplace_back(plant, plant_material, vec3{0.0, 1.0, 0.0});

    auto glasses = new model3D("../assets/models/glasses/glasses.obj", (float)(1.0f / 5.0f));
    auto glasses_texture = loadTex("../assets/models/glasses/glasses.jpg");
    Material glasses_material = {glasses_texture,
                                 { 1.0f, 1.0f, 1.0f, 1.0f },
                                 { 1.0f, 1.0f, 1.0f, 1.0f },
                                 { 1.0f, 1.0f, 1.0f, 1.0f },
                                 { 0, 0, 0 },
                                 20.0f };
    sceneObjects.emplace_back(glasses, glasses_material, vec3{0.5, 1.0, 0.0});

    auto rug = new model3D("../assets/models/rug/rug.obj", (float)(1.0f / 40.0f));
    auto rug_texture = loadTex("../assets/models/rug/rug.jpg");
    Material rug_material = {rug_texture,
                             { 1.0f, 1.0f, 1.0f, 1.0f },
                             { 1.0f, 1.0f, 1.0f, 1.0f },
                             { 1.0f, 1.0f, 1.0f, 1.0f },
                                 { 0, 0, 0 },
                                 80.0f };
    sceneObjects.emplace_back(rug, rug_material, vec3{0.0, 0.0, 0.0}, 1.57);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            mixColor = 0.5;
            mixTexture = 0.5;
            break;
        case GLUT_KEY_F2:
            mixColor = 0.0;
            mixTexture = 0.0;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple shaders");
    glClearColor(0.5, 0.5, 0.5, 0);

    GLenum glew_status = glewInit();
    if (GLEW_OK != glew_status)
    {
        std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
        return 1;
    }
    if (!GLEW_VERSION_2_0)
    {
        std::cout << "No support for OpenGL 2.0 found\n";
        return 1;
    }

    initShader();
    initScene();
    resizeWindow(600, 600);
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    freeShaders();
}