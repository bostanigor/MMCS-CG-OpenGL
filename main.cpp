#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
//#include "SOIL.lib"

using namespace std;

GLuint ballTexture;

static int w = 0, h = 0;
float rotate_x = 0;
float rotate_z = 0;
double rotate_tree = 0;

void Reshape(int width, int height) {
    w = width;
    h = height;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
}

void Cone(float diam, float h)
{
    float mat_amb[] = { 0.0, 0.0, 0.0, 1.0 };
    float mat_dif[] = { 0.0, 1.0, 0.0, 1.0 };
    float mat_spec[] = { 0.5, 0.5, 0.5, 1.0 };
    float shininess = 0.2 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glutSolidCone(diam, h, 100, 1);
}

void Ball(double radius, double indent, bool tex = true)
{
    if (tex)
    {
        GLUquadricObj* quadricObject;
        quadricObject = gluNewQuadric();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glEnable(GL_TEXTURE_2D);

        gluQuadricTexture(quadricObject, GL_TRUE);

        glTranslatef(indent, indent, 0);
        gluSphere(quadricObject, radius, 12, 12);
        glTranslatef(-indent, -indent, 0);

        gluDeleteQuadric(quadricObject);

        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glTranslatef(indent, indent, 0);
        glutSolidSphere(radius, 12, 12);
        glTranslatef(-indent, -indent, 0);
    }
}
void ballCycle(double cycleRadius)
{
    float mat_dif[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_amb[] = { 0.0, 0.0, 0.0, 1.0 };
    float mat_spec[] = { 0.1, 0.1, 0.1, 1.0 };
    float shininess = 1.0 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    int n = (2 * 3.1415 * cycleRadius) / 20;
    float angle = 360 / n;
    for (int i = 0; i < n; i++) {
        Ball(5, cycleRadius);
        glRotatef(angle, 0.0, 0.0, 1.0);
    }
}

void treeBalls()
{
    glTranslatef(0, 0, -75);
    glPushMatrix();
    ballCycle(40);
    glPopMatrix();

    glTranslatef(0, 0, 50);
    glPushMatrix();
    glRotatef(120, 0.0, 0.0, 1.0);
    ballCycle(32);
    glPopMatrix();

    glTranslatef(0, 0, 50);
    glPushMatrix();
    glRotatef(-120, 0.0, 0.0, 1.0);
    ballCycle(23);
    glPopMatrix();
}


void Garland(float indent, float height) {
    glPushMatrix();

    float mat_dif[] = {0.0, 0.0, 1.0, 1.0};
    float mat_amb[] = {0.0, 0.0, 1.0, 1.0};
    float mat_spec[] = {1.0, 1.0, 1.0, 1.0};
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    float mat_emmis[] = {0.0, 0.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);


    int n = 12;
    float angle = 360 / n;
    for (int i = 0; i < n; i++) {
        Ball(3, indent);
        glRotatef(angle, 0.0, 0.0, 1.0);
    }

    float new_mat_emmis[] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPopMatrix();
}


void Tree()
{
    glPushMatrix();
    glRotatef(rotate_tree, 0.0, 0.0, 1.0);

    float mat_amb[] = { 0.5 , 0.5 , 0.5 };
    float mat_dif[] = { 0.5 , 0.5 , 0.5 };
    float mat_spec[] = { 1 , 1 , 1 };
    float shininess = 1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glutSolidCylinder(10, 25, 150, 1);

    glTranslatef(0, 0, 25);
    Cone(70, 100);
    Garland(50, 100);

    glTranslatef(0, 0, 50);
    Cone(60, 80);
    Garland(45, 90);

    glTranslatef(0, 0, 50);
    Cone(50, 60);
    Garland(35, 70);

    treeBalls();

    glTranslatef(0, 0, 45);
    glPopMatrix();
}

void renderScene()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 300.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    glRotatef(rotate_x - 90, 1.0, 0.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -75);

    Tree();

    glEnable(GL_LIGHTING);
    GLfloat light0dir[] = { 0, 0, -1 };
    GLfloat light0loc[] = { 0, -100, 500, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0loc);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0dir);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);

    glColor3f(1, 1, 1);

    glEnable(GL_LIGHT0);

    glFlush();
    glutSwapBuffers();
}


void Update() {
    rotate_tree += 1;
    renderScene();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);

    glutCreateWindow("OpenGL");

    glClearColor(0.2f, 0.4f, 0.5f, 1.0f);


    //glLoadIdentity();
    //loadTextures();
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);

    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(Reshape);
    glutDisplayFunc(renderScene);
    glutIdleFunc(Update);
    //glutSpecialFunc(specialKeys);
    glutMainLoop();

    //GLfloat light0dir[] = { 1 , 1, 1 };


    ////glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
    ////glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
    ////glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
    //glLightfv(GL_LIGHT0, GL_POSITION, light0loc);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0dir);
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 100);
    //
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);

    return 0;
}
