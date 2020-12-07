#include <iostream>
#include <tuple>

#define GL_SILENCE_DEPRECATION
///Freeglut
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <cmath>

using namespace std;
#define PI 3.1415

static int w = 0, h = 0;

void Reshape(int width, int height) {
    w = width;
    h = height;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
}

void setPerspective() {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
    glutPostRedisplay();
}

float Angle = 0.0;

void renderTeapot() {
    setPerspective();
    glMatrixMode(GL_MODELVIEW);
    Angle += 0.05f;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 0.0f, 1.0f, 0.0f);

    glutWireTeapot(50.0f);
    glFlush();

    glutSwapBuffers();
}

void Update() {
    renderTeapot();
}

void Init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab 12");

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    Init();

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Update);
    glutIdleFunc(Update);
//  glutKeyboardFunc(cameraKeys);
//  glutSpecialFunc(carKeys);

    glutMainLoop();

    return 0;
}