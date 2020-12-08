#ifndef OPENGLABS_TASK4_H
#define OPENGLABS_TASK4_H

class task4 : public task {
    GLuint uniformAngle;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;

public:
    task4() {
        program = initShaderProgram("../shaders/cube.vs.c",
                                    "../shaders/cube.fs.c");

        uniformAngle = getUniformId("angle", program);
    }

    void update() override {
        rotate_x += 0.1;
        rotate_y += 0.1;
        rotate_z += 0.1;
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);

        glLoadIdentity();
        glUseProgram(program);
        double pi = 3.1415926535897932;

        glUniform3f(uniformAngle,
                    (GLfloat)(rotate_x * pi / 180),
                    (GLfloat)(rotate_y * pi / 180),
                    (GLfloat)(rotate_z * pi / 180));

        glBegin(GL_QUADS);
            glColor3f(0.0, 1.0, 1.0);
            glVertex3f(-0.5, -0.5, -0.5);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(-0.5, 0.5, -0.5);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-0.5, 0.5, 0.5);
            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(-0.5, -0.5, 0.5);

            glColor3f(1.0, 0.0, 1.0);
            glVertex3f(0.5, -0.5, -0.5);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.5, 0.5, -0.5);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(0.5, 0.5, 0.5);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(0.5, -0.5, 0.5);

            glColor3f(0.0, 1.0, 1.0);
            glVertex3f(-0.5, -0.5, -0.5);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(-0.5, 0.5, -0.5);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.5, 0.5, -0.5);
            glColor3f(1.0, 0.0, 1.0);
            glVertex3f(0.5, -0.5, -0.5);

            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(-0.5, -0.5, 0.5);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-0.5, 0.5, 0.5);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(0.5, 0.5, 0.5);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(0.5, -0.5, 0.5);

            glColor3f(0.0, 1.0, 1.0);
            glVertex3f(-0.5, -0.5, -0.5);
            glColor3f(1.0, 0.0, 1.0);
            glVertex3f(0.5, -0.5, -0.5);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(0.5, -0.5, 0.5);
            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(-0.5, -0.5, 0.5);

            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(-0.5, 0.5, -0.5);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.5, 0.5, -0.5);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(0.5, 0.5, 0.5);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-0.5, 0.5, 0.5);
        glEnd();

        glUseProgram(0);
        checkOpenGLerror();
        glFlush();
        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK4_H
