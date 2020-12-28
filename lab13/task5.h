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

    GLuint texture[2];

    GLuint program1;
    GLuint program2;
    GLuint program3;

    Material material0;
    Material material1;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;


    model3D model = model3D("../assets/models/monkey.obj", (float)(1.0f/150.0f));
    model3D model1 = model3D("../assets/models/stone_man.obj", (float)(1.0f / 10.0f));

public:
    task5() {
        program1 = initShaderProgram("../shaders/lab13/cube_phong_light.vs.c",
                                    "../shaders/lab13/cube_phong_light.fs.c");

        program2 = initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                                    "../shaders/lab13/toon_shading.fs.c");

        program3 = initShaderProgram("../shaders/lab13/blinn_phong_source.vs.c",
                                     "../shaders/lab13/bidirectional.fs.c");


        program = program1;
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../assets/glitter.jpg", &width, &height, &nrChannels, 0);
        unsigned char *data1 = stbi_load("../assets/glitter.jpg", &width, &height, &nrChannels, 0);

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(2, texture);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
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
                      { 0.7, 0.7, 0.7 });

        material0 = Material(texture[0],
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 1.0, 1.0, 1.0, 1.0 },
                      { 0.3, 0.3, 0.3, 1.0 },
                      { 1.0, 1.0, 1.0 },
                      1.0);

        material1 = Material(texture[1],
                             { 1.0, 1.0, 1.0, 1.0 },
                             { 1.0, 1.0, 1.0, 1.0 },
                             { 0.3, 0.3, 0.3, 1.0 },
                             { 1.0, 1.0, 1.0 },
                             1.0);

        material = material0;

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
        rotate_z += 0.1;

        //light.position = {  2 * (GLfloat)cos(rotate_z), 0.0,  2 * (GLfloat)sin(rotate_z)};
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
        glBindTexture(GL_TEXTURE_2D, texture[0]);

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
            case GLUT_KEY_F9:
                material = material0;
                break;
            case GLUT_KEY_F10:
                material = material1;
                break;
        }
        glUseProgram(program);
        render();
    }
};

#endif //OPENGLABS_TASK5_H
