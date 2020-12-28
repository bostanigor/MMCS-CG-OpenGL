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
GLfloat cameraDistance = 2.0f;

UniformStruct uniformLight;
UniformStruct uniformMaterial;
UniformStruct uniformTransform;

Light light = Light({ 10.0, 0.0f, 0.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0, 1.0 },
                    { 1.0, 1.0, 1.0 });
// True position of light
vec4 lightPos = { 0.0, 0.0, 0.0, 1.0f };

Material * material;
Transform * transform = new Transform {
        {}, {},

        {1.0, 0.0, 0.0,
         0.0, 1.0, 0.0,
         0.0, 0.0, 1.0},

        { 0.0, 0.0, 0.0f}
};

mat4 cameraMatrix;

std::vector<sceneObject> sceneObjects;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    light.setUniform(shader, uniformLight);

    for (auto object : sceneObjects) {
        material = &(object.material);
        transform->model = cameraMatrix * object.getModelTransform();

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
    angleY += 0.01f;
    vec3 cameraPos = {
            cameraDistance * sin(angleY),
            0.0,
            cameraDistance * cos(angleY)
    };
    transform->viewPosition = cameraPos;

    auto t = lightPos;
    cameraMatrix = offsetMatrix(-cameraPos) * rotationYMatrix(angleY);
    light.position = cameraMatrix * lightPos;
    t = cameraMatrix * t;
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
//    shader = initShaderProgram("../shaders/lab13/cube_phong_light.vs.c",
//                               "../shaders/lab13/cube_phong_light.fs.c");
    shader = initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                               "../shaders/lab13/toon_shading.fs.c");
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
                          { 1.0f, 0.5f, 0.31f, 1.0f },
                          { 1.0f, 0.5f, 0.31f, 1.0f },
                          { 0.5f, 0.5f, 0.5f, 1.0f },
                          { 0, 0, 0 },
                          32.0f };
    sceneObjects.emplace_back(cat_m, material, vec3{0.0, 0.0f, 0.0});
//    cat = sceneObject(cat_m, material);
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
//    glutSpecialFunc(specialKeys);
    glutMainLoop();
    //! ќсвобождение ресурсов
    freeShaders();
}