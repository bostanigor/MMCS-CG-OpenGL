#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "../common/transformations.h"
#include "../common/model3D.h"
#include "../common/sceneObject.h"
#include "my_objects.h"
#include <cmath>
#include <iostream>

#define PI 3.1415

std::vector<GLuint> shaders;
GLuint currentShader;

int width, height;
GLfloat angleY = 0.0f;
GLfloat cameraDistance = 3.0f;

UniformStruct uniformLight;
UniformStruct uniformMaterial;
UniformStruct uniformTransform;

Light light = Light({ 0.0, 0.0, 0.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0 });

Light turnedOffLight = Light({ 0.0, 0.0, 0.0, 0.0 },
                            { 0.0, 0.0, 0.0, 0.0 },
                            { 0.0, 0.0, 0.0, 0.0 },
                            { 0.0, 0.0, 0.0, 0.0 },
                            { 0.0, 0.0, 0.0 });
bool lightsOn = true;

Material * material;

mat4 perspectiveMatrix;
Transform * transform = new Transform {
        {}, {},

        //! normals
        {1.0, 0.0, 0.0,
         0.0, 1.0, 0.0,
         0.0, 0.0, 1.0},

        { 0.0, 0.0, 0.0f}
};

mat4 cameraMatrix;

std::vector<sceneObject*> sceneObjects;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    if (lightsOn)
        light.setUniform(currentShader, uniformLight);
    else
        turnedOffLight.setUniform(currentShader, uniformLight);

    transform->viewProjection = cameraMatrix * perspectiveMatrix;

    for (auto object : sceneObjects) {
        material = &(object->material);
        transform->model = object->getModelTransform();

        material->setUniform(currentShader, uniformMaterial);
        transform->setUniform(currentShader, uniformTransform);

        object->render();
    }

    glFlush();
    glutSwapBuffers();
}

void update() {
    angleY += 0.01f;
    vec3 cameraPos = {
            cameraDistance * sin(angleY),
            0.0,
            cameraDistance * cos(angleY)
    };
    transform->viewPosition = cameraPos;

    cameraMatrix = offsetMatrix(-cameraPos) * rotationYMatrix(angleY);

    auto floatingEye = sceneObjects[2];
    floatingEye->rotateOY(-0.03f);
    light.position = floatingEye->position;

    render();
}

void setPerspective(float fov, float aspectRatio, float nearf, float farf) {
    float f = 1.0f / tan(fov * PI / 360);
    perspectiveMatrix = {
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
    for (auto shader : shaders)
        glDeleteProgram(shader);
}

void initShader() {
    shaders.push_back(initShaderProgram("../shaders/lab13/cube_phong_light.vs.c",
                               "../shaders/lab13/cube_phong_light.fs.c"));
    shaders.push_back(initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                               "../shaders/lab13/toon_shading.fs.c"));
    shaders.push_back(initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                               "../shaders/lab13/bidirectional.fs.c"));

    currentShader = shaders[0];
    glUseProgram(currentShader);

    uniformLight = UniformStruct("light", {
            "position",
            "ambient",
            "diffuse",
            "specular",
            "attenuation",
    }, shaders);
    uniformMaterial = UniformStruct("material", {
            "texture",
            "ambient",
            "diffuse",
            "specular",
            "emission",
            "shininess",
    }, shaders);
    uniformTransform = UniformStruct("transform", {
            "model",
            "viewProjection",
            "normal",
            "viewPosition"
    }, shaders);
}

void initScene() {
    sceneObjects.push_back(fox());
    sceneObjects.push_back(tree());
    sceneObjects.push_back(eye());
    sceneObjects.push_back(floor());
    sceneObjects.push_back(boxes());
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1: lightsOn = !lightsOn; break;
        case GLUT_KEY_F2: currentShader = shaders[0]; break;
        case GLUT_KEY_F3: currentShader = shaders[1]; break;
        case GLUT_KEY_F4: currentShader = shaders[2]; break;
    }
    glUseProgram(currentShader);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple shaders");
    glClearColor(0, 0, 0, 0);
    //! ќб€зательно перед инициализацией шейдеров
    GLenum glew_status = glewInit();
    if (GLEW_OK != glew_status)
    {
        //! GLEW не проинициализировалась
        std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
        return 1;
    }
    //! ѕровер€ем доступность OpenGL 2.0
    if (!GLEW_VERSION_2_0)
    {
        //! OpenGl 2.0 оказалась не доступна
        std::cout << "No support for OpenGL 2.0 found\n";
        return 1;
    }
    //! »нициализаци€ шейдеров
    initShader();
    initScene();
    resizeWindow(600, 600);
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    //! ќсвобождение ресурсов
    freeShaders();
}