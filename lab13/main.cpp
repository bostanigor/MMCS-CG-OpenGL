#include <iostream>
#include <tuple>

#define GL_SILENCE_DEPRECATION
///Freeglut
#include <GL/glew.h>
#include <GL/freeglut.h>
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

float angle = 0.0;

void renderTeapot() {
    setPerspective();
    glMatrixMode(GL_MODELVIEW);
//  angle += 0.05f;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0, 1.0, 1.0);
    glutWireTeapot(50.0f);
    glFlush();

    glutSwapBuffers();
}

void Update() {
    renderTeapot();
    angle += 0.1f;
}

void Init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab 12");

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(Reshape);
    glutDisplayFunc(renderTeapot);
    glutIdleFunc(Update);
    Init();
//  glutKeyboardFunc(cameraKeys);
//  glutSpecialFunc(carKeys);

    glutMainLoop();

    return 0;
}