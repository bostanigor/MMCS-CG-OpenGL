#include <iostream>
#include <tuple>

#define GL_SILENCE_DEPRECATION
///Freeglut
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <cmath>
///Apple's GLUT
//#include <GLUT/glut.h>

#include "Car.h"

using namespace std;
#define PI 3.1415

static int w = 0, h = 0;
double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;
double tree_rotation;
bool lights = false;

auto car = Car();

GLuint floorTexture, ballTexture;

std::tuple<float, float, float> coordinates() {
    float m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    return std::make_tuple(m[0], m[5], m[10]);
}

void turnLights() {
  if (lights) {
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
  }
  else {
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
  }
  lights = !lights;
}

void Reshape(int width, int height) {
    w = width;
    h = height;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
}

void cameraKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            rotate_x += 5;
            break;
        case 's':
            rotate_x -= 5;
            break;
        case 'q':
            rotate_y += 5;
            break;
        case 'e':
            rotate_y -= 5;
            break;
        case 'a':
            rotate_z += 5;
            break;
        case 'd':
            rotate_z -= 5;
            break;
    }
    glutPostRedisplay();
}

void carKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            car.move(5);
            break;
        case GLUT_KEY_DOWN:
            car.move(-5);
            break;
        case GLUT_KEY_RIGHT:
            car.turn(2);
            break;
        case GLUT_KEY_LEFT:
            car.turn(-2);
            break;
        case GLUT_KEY_F1:
            car.turn_lights();
            break;
        case GLUT_KEY_F2:
            turnLights();
    }
    glutPostRedisplay();
}

void cone(float diam, float h) {
    float mat_amb[] = {0.0, 0.0, 0.0, 1.0};
    float mat_dif[] = {0.0, 1.0, 0.0, 1.0};
    float mat_spec[] = {0.5, 0.5, 0.5, 1.0};
    float shininess = 0.2 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glutSolidCone(diam, h, 100, 1);
}

void ball(double radius, double offset, bool tex = true) {
    if (tex) {
        GLUquadricObj *quadObj;
        quadObj = gluNewQuadric();
        glBindTexture(GL_TEXTURE_2D, ballTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glEnable(GL_TEXTURE_2D);

        gluQuadricTexture(quadObj, GL_TRUE);

        glTranslatef(offset, offset, 0);
        gluSphere(quadObj, radius, 12, 12);
        glTranslatef(-offset, -offset, 0);

        gluDeleteQuadric(quadObj);

        glDisable(GL_TEXTURE_2D);
    } else {
        glTranslatef(offset, offset, 0);
        glutSolidSphere(radius, 12, 12);
        glTranslatef(-offset, -offset, 0);
    }
}

void ballsCycle(double cycleRadius) {
    float mat_dif[] = {1.0, 1.0, 1.0, 1.0};
    float mat_amb[] = {0.0, 0.0, 0.0, 1.0};
    float mat_spec[] = {0.1, 0.1, 0.1, 1.0};
    float shininess = 1.0 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    int n = (2 * PI * cycleRadius) / 20;
    double angle = 360 / n;
    for (int i = 0; i < n; i++) {
        ball(5, cycleRadius);
        glRotatef(angle, 0.0, 0.0, 1.0);
    }
}

void ballsToTree() {
    glTranslatef(0, 0, -75);
    glPushMatrix();
    ballsCycle(40);
    glPopMatrix();

    glTranslatef(0, 0, 50);
    glPushMatrix();
    glRotatef(120, 0.0, 0.0, 1.0);
    ballsCycle(32);
    glPopMatrix();

    glTranslatef(0, 0, 50);
    glPushMatrix();
    glRotatef(-120, 0.0, 0.0, 1.0);
    ballsCycle(23);
    glPopMatrix();
}

void garland(float off, float height) {
    glPushMatrix();

    float diffuse[] = {0.0, 0.0, 1.0, 1.0};
    float ambient[] = {0.0, 0.0, 1.0, 1.0};
    float specular[] = {1.0, 1.0, 1.0, 1.0};
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    float emission[] = {0.0, 0.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    int count = 12;
    float angle = 360 / (count * 1.0);
    for (int i = 0; i < count; i++) {
        ball(3, off, false);
        glRotatef(angle, 0.0, 0.0, 1.0);
    }

    float new_emission[] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPopMatrix();
}

void christmasTree() {
    glPushMatrix();
    glRotatef(tree_rotation, 0.0, 0.0, 1.0);

    float ambient[] = {0.5, 0.5, 0.5};
    float diffuse[] = {0.5, 0.5, 0.5};
    float specular[] = {1, 1, 1};
    float shininess = 1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glutSolidCylinder(10, 25, 150, 1);

    glTranslatef(0, 0, 25);
    cone(70, 100);
    garland(50, 100);

    glTranslatef(0, 0, 50);
    cone(60, 80);
    garland(45, 90);

    glTranslatef(0, 0, 50);
    cone(50, 60);
    garland(35, 70);

    ballsToTree();

    glTranslatef(0, 0, 45);
    glPopMatrix();
}

void loadTextures() {
    floorTexture = SOIL_load_OGL_texture("../assets/floor.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ballTexture = SOIL_load_OGL_texture("../assets/glitter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                        SOIL_FLAG_INVERT_Y);
}

void addFloor(int x, int y, int z, int size) {
    glBindTexture(GL_TEXTURE_2D, floorTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x + size, y + size, z);
    glTexCoord2f(0.0, 30.0);
    glVertex3f(x + size, y - size, z);
    glTexCoord2f(30.0, 30.0);
    glVertex3f(x - size, y - size, z);
    glTexCoord2f(30.0, 0.0);
    glVertex3f(x - size, y + size, z);
    glEnd();

    gluNewQuadric();

    glDisable(GL_TEXTURE_2D);
}

void addPole(GLenum light) {
    glPushMatrix();

    float diffuse[] = {0.4, 0.4, 0.4};
    float ambient[] = {0.3, 0.3, 0.23};
    float specular[] = {1, 1, 1};
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glColor3f(0.4, 0.4, 0.4); // ЦВЕТ СТОЛБА

    glutSolidCylinder(2, 150, 12, 1);
    glTranslatef(0, 0, 150);

    if (lights) {
        float emission[] = {250 / 255.0, 255 / 255.0, 150 / 255.0};
        const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        const GLfloat position[] = { 0.0, 0.0, 0.0, 1.0};

        glLightfv(light, GL_DIFFUSE, light_diffuse);
        glLightfv(light, GL_SPECULAR, light_specular);
        glLightfv(light, GL_POSITION, position);
        glLightf(light, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(light, GL_LINEAR_ATTENUATION, 0.05);
        glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    }

    float new_diffuse[] = {250 / 255.0, 255 / 255.0, 150 / 255.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new_diffuse);

    glutSolidSphere(8, 10, 10);
    glTranslatef(0, 0, 25);

    glTranslatef(0, 0, -20);

    float mat_emmis[] = {0, 0, 0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);

    float new_diffuse2[] = {0.4, 0.4, 0.4};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new_diffuse2);

    glPopMatrix();
}

void addPoles() {
    glTranslatef(160, 0, 0);
    addPole(GL_LIGHT3);
    glTranslatef(-320, 0, 0);
    addPole(GL_LIGHT4);
    glTranslatef(0, 320, 0);
    addPole(GL_LIGHT5);
    glTranslatef(320, 0, 0);
    addPole(GL_LIGHT6);
}

void addStreet() {
    glPushMatrix();

    auto m = coordinates();
    addFloor(get<0>(m), get<1>(m), get<2>(m), 2000);

    addPoles();

    glPopMatrix();
}

void addSun() {
  const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  const GLfloat direction[] = { 0.0, 0.0, 1.0, 0.0};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);
}

void renderScene() {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(rotate_x - 90, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -75);

    addStreet();
    christmasTree();
    car.render();

    addSun();

    glFlush();
    glutSwapBuffers();
}

void Update() {
    tree_rotation += 1;
    renderScene();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Christmas tree");

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    loadTextures();
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    tree_rotation = 0;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glutReshapeFunc(Reshape);
    glutDisplayFunc(renderScene);
    glutIdleFunc(Update);
    glutKeyboardFunc(cameraKeys);
    glutSpecialFunc(carKeys);

    glutMainLoop();

    return 0;
}