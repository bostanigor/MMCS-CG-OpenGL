#ifndef OPENGLABS_TASK4_H
#define OPENGLABS_TASK4_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "../common/model3D.h"
#include "../common/stb_image.h"

class task4 : public task {
    GLuint uniformAngle;
    GLuint texture;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;

    model3D model = model3D("../assets/models/hexahedron.obj");

public:
    task4() {
        program = initShaderProgram("../shaders/lab13/standard.vs.c",
                                    "../shaders/lab13/cube_textured.fs.c");
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../assets/pumpkin.jpg", &width, &height, &nrChannels, 0);

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        uniformAngle = getUniformId("angle", program);

    }

    void update() override {
        rotate_z += 1.0;
        rotate_x += 1.0;
//        rotate_z += 0.1;
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
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(model.VAO);
        glDrawArrays(GL_TRIANGLES, 0, model.elementCount);
        glBindVertexArray(0);

        glFlush();

        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK4_H
