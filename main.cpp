#include <iostream>

#define GL_SILENCE_DEPRECATION
///Freeglut
#include <GL/glew.h>
#include <GL/freeglut.h>
///Apple's GLUT
//#include <GLUT/glut.h>
using namespace std;

static int w = 0, h = 0;
float rotate_x = 0;
float rotate_y = 0;
float ambient[] = {0.2, 0.2, 0.2, 1.0};
float greencolor[] = {0.2, 0.8, 0.0, 0.8};
float treecolor[] = {0.9, 0.6, 0.3, 0.8};
float lightpos[] = {1.0, 1.0, 1.0};

void Init() {
    glClearColor(0.5, 0.5, 0.5, 1.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

}

void Reshape(int width, int height) {
    w = width;
    h = height;
}

void orthogonal() {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutPostRedisplay();
}

void perspective() {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
    glutPostRedisplay();
}


void renderChristmasTree() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, treecolor);
    glTranslatef(0.0, 0.0, -0.7);

    glutSolidCylinder(0.1, 0.2, 20, 20);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greencolor);
    glTranslatef(0.0, 0.0, 0.2);

    glutSolidCone(0.5, 0.5, 20, 20);
    glTranslatef(0.0, 0.0, 0.3);
    glutSolidCone(0.4, 0.4, 20, 20);
    glTranslatef(0.0, 0.0, 0.3);
    glutSolidCone(0.3, 0.3, 20, 20);

    glPopMatrix();
    glutSwapBuffers();
}


void Update() {
    renderChristmasTree();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("OpenGL");
    Init();

    glutIdleFunc(Update);
    glutDisplayFunc(Update);
    glutReshapeFunc(Reshape);
//    glutSpecialFunc(changeAnimation);

    glutMainLoop();

    return 0;
}