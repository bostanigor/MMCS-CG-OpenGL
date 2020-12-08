#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common.h"

class task1 {
    GLuint program;

    GLuint uniformAngle;

    float angleVal;

public:
    task1() {
        program = initShaderProgram("../shaders/rotate_vertices_x.vs.c",
                                    "../shaders/color_fragment.fs.c");
        uniformAngle = getUniformId("angle", program);
        angleVal = 0.0;
        glUseProgram(program);
    }

    void enableShaders() const {
        glUseProgram(program);
    }

    void update() {
        angleVal += 0.1;
        render();
    }

    GLuint getProgram() const {
        return program;
    }

    void render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        //! Передаем юниформ в шейдер
        glUniform1f(uniformAngle, angleVal);

        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.0f);
            glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.0f);
            glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5f, 0.5f, 0.0f);
        glEnd();

        glFlush();
//        checkOpenGLerror();

        glutSwapBuffers();
    }
};
