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
    GLuint program3;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;


    model3D model = model3D("../assets/models/stone_man.obj", (float)(1.0f / 10.0f));

public:
    task5() {
        program1 = initShaderProgram("../shaders/lab13/cube_phong_light.vs.c",
                                    "../shaders/lab13/cube_phong_light.fs.c");

        program2 = initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                                    "../shaders/lab13/toon_shading.fs.c");

//        program3 = initShaderProgram("../shaders/lab13/standard.vs.c",
//                                    "../shaders/lab13/cube_textured.fs.c");

        program3 = initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                                     "../shaders/lab13/bidirectional.fs.c");


        program = program1;
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../assets/floor.jpg", &width, &height, &nrChannels, 0);

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        uniformLight = UniformStruct("light", {
                "position",
                "ambient",
                "diffuse",
                "specular",
                "attenuation",
            }, { program1, program2, program3 } );
        uniformMaterial = UniformStruct("material", {
                "texture",
                "ambient",
                "diffuse",
                "specular",
                "emission",
                "shininess",
            }, { program1, program2, program3 } );
        uniformTransform = UniformStruct("transform", {
                "model",
                "viewProjection",
                "normal",
                "viewPosition"
        }, { program1, program2, program3 } );

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
        rotate_z += 0.01;

        light.position = {  2 * (GLfloat)cos(rotate_z), 0.0,  2 * (GLfloat)sin(rotate_z)};
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);

        light.setUniform(program, uniformLight);
        material.setUniform(program, uniformMaterial);
        transform.setUniform(program, uniformTransform);

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
                program = program1;
                break;
            case GLUT_KEY_F7:
                program = program2;
                break;
            case GLUT_KEY_F8:
                program = program3;
                break;
        }
        glUseProgram(program);
        render();
    }
};

#endif //OPENGLABS_TASK5_H
