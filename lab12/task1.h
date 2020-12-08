#ifndef OPENGLABS_TASK1_H
#define OPENGLABS_TASK1_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common.h"

class task1 : public task {
    GLuint uniformAngle;

    float angleVal;

public:
    task1() {
        program = initShaderProgram("../shaders/rotate_vertices_x.vs.c",
                                    "../shaders/color_fragment.fs.c");
        uniformAngle = getUniformId("angle", program);
        angleVal = 0.0f;
    }

    void update() override {
        angleVal += 0.1;
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT);
        //! Передаем юниформ в шейдер
        glUniform1f(uniformAngle, angleVal);

        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); glVertex2f(-0.5f, -0.5f);
            glColor3f(0.0, 1.0, 0.0); glVertex2f(-0.5f, 0.5f);
            glColor3f(0.0, 0.0, 1.0); glVertex2f(0.5f, 0.5f);
        glEnd();

        glFlush();

        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK1_H
