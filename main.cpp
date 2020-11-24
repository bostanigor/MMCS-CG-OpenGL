#include <iostream>

#define GL_SILENCE_DEPRECATION
///Freeglut
#include <GL/glew.h>
#include <GL/freeglut.h>
///Apple's GLUT
//#include <GLUT/glut.h>
using namespace std;

static int w = 0, h = 0;
static float Angle = 0;
static int currentAnimationNumber = 0;

void Init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void setOrthogonal() {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glutPostRedisplay();
}

void setPerspective() {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
  glutPostRedisplay();
}

void Reshape(int width, int height) {
  w = width;
  h = height;
//  setPerspective();
}

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;

void changeAnimation(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT)
        currentAnimationNumber++;
    if (key == GLUT_KEY_LEFT)
        currentAnimationNumber--;
    currentAnimationNumber = (currentAnimationNumber + 8) % 8;
}

void renderRectangle() {
    setOrthogonal();
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    rotate_z++;

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5f, 0.5f);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5f, 0.5f);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void renderWireCube() {
    setOrthogonal();
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    glutWireCube(1);
    glScalef(10, 10, 10);

    glFlush();
    glutSwapBuffers();

    rotate_x++;
    rotate_y++;
    rotate_z++;
}

void renderSolidCube() {
    setOrthogonal();
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    glutSolidCube(1);

    glFlush();
    glutSwapBuffers();

    rotate_x++;
    rotate_y++;
    rotate_z++;
}

void renderSphere() {
    setPerspective();
    glMatrixMode(GL_MODELVIEW);
    Angle += 0.5f;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 0.0f, 1.0f, 0.0f);
    glutWireSphere(50.0f, 100, 100);

    glFlush();
    glutSwapBuffers();
}

void renderTeapot() {
    setPerspective();
    glMatrixMode(GL_MODELVIEW);
    Angle += 0.5f;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 0.0f, 1.0f, 0.0f);

    glutWireTeapot(50.0f);
    glFlush();

    glutSwapBuffers();
}


void renderDots() {
    setPerspective();
    glPointSize(10.0f);

    glMatrixMode(GL_MODELVIEW);
    Angle += 0.5f;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_POINTS);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glEnd();
    glFlush();

    glutSwapBuffers();
}

void renderTriangles() {
    setPerspective();
    glMatrixMode(GL_MODELVIEW);
    Angle += 0.5f;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-75.0f, 0.0f, -50.0f);
    glVertex3f(-75.0f, 0.0f, 50.0f);
    glVertex3f(75.0f, 0.0f, 50.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-75.0f, 0.0f, -50.0f);
    glVertex3f(75.0f, 0.0f, -50.0f);
    glVertex3f(75.0f, 0.0f, 50.0f);

    glEnd();
    glFlush();

    glutSwapBuffers();
}

void renderGradientTriangle() {
    setPerspective();
    glMatrixMode(GL_MODELVIEW);
    Angle += 0.5f;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 1.0f, 0.0f, 0.0f);
    glRotatef(Angle, 0.0f, 1.0f, 0.0f);
    glRotatef(Angle, 0.0f, 0.0f, 1.0f);

    GLfloat BlueCol[3] = {0, 0, 1};
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3ub(0, 255, 0);
    glVertex3f(75.0, 0.0, 0.0);
    glColor3fv(BlueCol);
    glVertex3f(75.0, 75.0, 0.0);

    glEnd();
    glFlush();

    glutSwapBuffers();
}

void Update() {
    switch (currentAnimationNumber) {
        case 0:
//            renderSphere();
            renderRectangle();
            break;
        case 1:
            renderWireCube();
            break;
        case 2:
            renderSolidCube();
            break;
        case 3:
//            renderRectangle();
            renderSphere();
            break;
        case 4:
            renderTeapot();
            break;
        case 5:
            renderDots();
            break;
        case 6:
            renderTriangles();
            break;
        case 7:
            renderGradientTriangle();
            break;
    }
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
    glutSpecialFunc(changeAnimation);

    glutMainLoop();

    return 0;
}
