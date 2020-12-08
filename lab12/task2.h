#ifndef OPENGLABS_TASK2_H
#define OPENGLABS_TASK2_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common.h"

class task2 : public task {
    GLuint uniformColor1;
    GLuint uniformColor2;

public:
    task2() {
        program = initShaderProgram("../shaders/vertices_2d_to_3d.vs.c",
                                    "../shaders/stripes.fs.c");
        uniformColor1 = getUniformId("color1", program);
        uniformColor2 = getUniformId("color2", program);
    }

    void update() override {
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT);
        static float color1[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
        static float color2[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

        //! Передаем юниформ в шейдер
        glUniform4fv(uniformColor1, 1, color1);
        glUniform4fv(uniformColor2, 1, color2);

        glBegin(GL_QUADS);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(-0.5f, 0.5f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(0.5f, -0.5f);
        glEnd();

        glFlush();

        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK2_H
