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

UniformStruct uniformLight;
UniformStruct uniformMaterial;
UniformStruct uniformTransform;

Light light = Light({ 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
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

std::vector<sceneObject> sceneObjects;

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

void initShader() {
    shader = initShaderProgram("../shaders/lab13/cube_phong_light.vs.c",
                               "../shaders/lab13/cube_phong_light.fs.c");
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
}

void initScene() {
//    auto cat_m = new model3D("../assets/models/cat/cat.obj", 1.0f / 100.0f);
//    auto cat_t = loadTex("../assets/models/cat/cat.jpg");
    auto cat_m = new model3D("../assets/models/cube.obj", (float)(1.0f / 1.0f));
    auto cat_t = loadTex("../assets/floor.jpg");
    Material material = { cat_t,
                          { 1.0, 1.0, 1.0, 1.0 },
                          { 1.0, 1.0, 1.0, 1.0 },
                          { 0.3, 0.3, 0.3, 1.0 },
                          { 1.0, 1.0, 1.0 },
                          1.0 };
    sceneObjects.emplace_back(cat_m, material, vec3{0.0, 0.0, 0.0});
//    cat = sceneObject(cat_m, material);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    light.setUniform(shader, uniformLight);

    for (auto object : sceneObjects) {
        material = &(object.material);
        transform->model = object.getModelTransform();

        material->setUniform(shader, uniformMaterial);
        transform->setUniform(shader, uniformTransform);

        object.render();
    }

    glFlush();
    glutSwapBuffers();
}

void update() {
//    sceneObjects[0].position.z -= 10.0f;
//    transform->viewPosition.z -= 0.01f;
    render();
}

void freeShaders() {
    glDeleteProgram(shader);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple shaders");
    glClearColor(0, 0, 0, 0);

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
    glutMainLoop();
    freeShaders();
}