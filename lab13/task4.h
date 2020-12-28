#ifndef OPENGLABS_TASK4_H
#define OPENGLABS_TASK4_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "../common/model3D.h"
#include "../common/stb_image.h"

class task4 : public task {
    GLuint uniformAngle;
    GLuint texture[2];

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;

    model3D model = model3D("../assets/models/monkey.obj", (float)(1.0f/150.0f));
    model3D model1 = model3D("../assets/models/stone_man.obj", (float)(1.0f/10.0f));

public:
    task4() {
        int width, height, nrChannels;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../assets/glitter.jpg", &width, &height, &nrChannels, 0);
        //stbi_set_flip_vertically_on_load(true);
        unsigned char *data1 = stbi_load("../assets/glitter.jpg", &width, &height, &nrChannels, 0);

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(2, texture);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        program = initShaderProgram("../shaders/lab13/standard_offset.vs.c",
                                    "../shaders/lab13/cube_textured.fs.c");
        //rotate_z = 90;
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);

        uniformAngle = getUniformId("angle", program);

    }

    void update() override {
        //rotate_z += 0.1;
        //rotate_x += 0.1;
        rotate_y += 0.3;
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);

        double pi = 3.1415926535897932;
        glUniform3f(uniformAngle,
                    (GLfloat)(rotate_x * pi / 180),
                    (GLfloat)(rotate_y * pi / 180),
                    (GLfloat)(rotate_z * pi / 180));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glBindVertexArray(model.VAO);
        glDrawArrays(GL_TRIANGLES, 0, model.elementCount);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

        glBindVertexArray(model1.VAO);
        glDrawArrays(GL_TRIANGLES, 0, model1.elementCount);
        glBindVertexArray(0);

        glFlush();

        glutSwapBuffers();
    }

    void special(int key) override { }
};

#endif //OPENGLABS_TASK4_H
