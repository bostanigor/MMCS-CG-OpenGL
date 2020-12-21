#ifndef OPENGLABS_TASK5_H
#define OPENGLABS_TASK5_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "../common/model3D.h"
#include "../common/stb_image.h"

class task5 : public task {
    GLuint uniformAngle;
    UniformStruct uniformLight;
    UniformStruct uniformMaterial;
    UniformStruct uniformTransform;

    Light light;
    Material material;
    Transform transform;

    GLuint texture;

    GLuint program1;
    GLuint program2;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;


    model3D model = model3D("../assets/models/stone_man.obj", (float)(1.0f / 10.0f));

public:
    task5() {
        program = initShaderProgram("../shaders/lab13/cube_phong_light.vs.c",
                                    "../shaders/lab13/cube_phong_light.fs.c");

        program1 = initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                                    "../shaders/lab13/toon_shading.fs.c");

        program2 = initShaderProgram("../shaders/lab13/standard.vs.c",
                                    "../shaders/lab13/cube_textured.fs.c");
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../assets/floor.jpg", &width, &height, &nrChannels, 0);

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

//        uniformAngle = getUniformId("angle", program);

        uniformLight = UniformStruct("light", {
                "position",
                "ambient",
                "diffuse",
                "specular",
                "attenuation",
            }, program );
        uniformMaterial = UniformStruct("material", {
                "texture",
                "ambient",
                "diffuse",
                "specular",
                "emission",
                "shininess",
            }, program );
        uniformTransform = UniformStruct("transform", {
                "model",
                "viewProjection",
                "normal",
                "viewPosition"
        }, program );

        light = Light({ 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0 });

        material = Material(texture,
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0 },
                      1.0);

        transform = {
                        {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, -1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0},

                        {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0},

                        {1.0, 0.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 0.0, 1.0},

                        { 0.0, 0.0, 0.0}
        };
    }

    void update() override {
        /*rotate_z += 0.1;
        rotate_x += 0.1;*/
        rotate_z += 0.1;

        light.position = {  2 * (GLfloat)cos(rotate_z), 0.0,  2 * (GLfloat)sin(rotate_z)};
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);

        double pi = 3.1415926535897932;
        /*glUniform3f(uniformAngle,
                    (GLfloat)(rotate_x * pi / 180),
                    (GLfloat)(rotate_y * pi / 180),
                    (GLfloat)(rotate_z * pi / 180));*/


        light.setUniform(uniformLight);
        material.setUniform(uniformMaterial);
        transform.setUniform(uniformTransform);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(model.VAO);
        glDrawArrays(GL_TRIANGLES, 0, model.elementCount);
        glBindVertexArray(0);

        glFlush();

        glutSwapBuffers();
    }

    void special(int key) override {
        switch(key) {
            case GLUT_KEY_F6:
                glUseProgram(program);
                break;
            case GLUT_KEY_F7:
                glUseProgram(program1);
                break;
            case GLUT_KEY_F8:
                glUseProgram(program2);
                break;
        }
        render();
    }
};

#endif //OPENGLABS_TASK5_H
