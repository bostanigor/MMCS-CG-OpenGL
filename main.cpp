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
using namespace std;
#define PI 3.1415926538

static int w = 0, h = 0;
double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;
double tree_rot;
bool wire;
bool ligth_toggle = false;

GLuint floorTexture, ballTexture;

std::tuple<float, float, float> getCoords()
{
    float m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    return std::make_tuple(m[0], m[5], m[10]);
}

void Reshape(int width, int height) {
    w = width; h = height;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: rotate_x += 5; break;
        case GLUT_KEY_DOWN: rotate_x -= 5; break;
        case GLUT_KEY_RIGHT: rotate_y += 5; break;
        case GLUT_KEY_LEFT: rotate_y -= 5; break;
        case GLUT_KEY_PAGE_UP: rotate_z += 5; break;
        case GLUT_KEY_PAGE_DOWN: rotate_z -= 5; break;
        case GLUT_KEY_F1: ligth_toggle = !ligth_toggle; break;
    }
    glutPostRedisplay();
}

void addCone(float diam, float h)
{
    float mat_dif[] = { 0 , 1 , 0 };
    float mat_amb[] = { 0 , 0 , 0 };
    float mat_spec[] = { 1 , 1 , 1 };
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //glColor3f(0, 1, 0);
    if (wire)
        glutWireCone(diam, h, 12, 1);
    else
        glutSolidCone(diam, h, 12, 1);
}

void addBall(double radius, double offset, bool tex = true)
{
    if (tex)
    {
        GLUquadricObj* quadObj;
        quadObj = gluNewQuadric();

        glBindTexture(GL_TEXTURE_2D, ballTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glEnable(GL_TEXTURE_2D);

        gluQuadricTexture(quadObj, GL_TRUE);

        glTranslatef(offset, offset, 0);
        if (wire)
            glutWireSphere(radius, 12, 12);
        else
            gluSphere(quadObj, radius, 12, 12);
        //glutSolidSphere(radius, 12, 12);
        glTranslatef(-offset, -offset, 0);

        gluDeleteQuadric(quadObj);

        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glTranslatef(offset, offset, 0);
        if (wire)
            glutWireSphere(radius, 12, 12);
        else
            glutSolidSphere(radius, 12, 12);
        glTranslatef(-offset, -offset, 0);
    }
}
void addCycleOFBalls(double cycleRadius)
{
    //glColor3f(1, 0, 0); // ЦВЕТ ШАРИКА

    float mat_dif[] = { 1 , 1 , 1 };
    float mat_amb[] = { 0 , 0 , 0 };
    float mat_spec[] = { 0.1 , 0.1 , 0.1 };
    float shininess = 1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    addBall(5, cycleRadius);

    glTranslatef(2, 2, -5);
    glRotatef(90, 0.0, 0.0, 1.0);
    addBall(7, cycleRadius);

    glTranslatef(-2, -2, 5);
    glRotatef(90, 0.0, 0.0, 1.0);
    addBall(6, cycleRadius);

    glTranslatef(4, 4, -10);
    glRotatef(90, 0.0, 0.0, 1.0);
    addBall(8, cycleRadius);
}

void addStar()
{
    auto m = getCoords();
//    addFloor(get<0>(m), get<1>(m), get<2>(m), 2000);

//    float* m = getCoords();
    float x = get<0>(m);
    float y = get<1>(m);
    float z = get<2>(m);
    float t = 0;
    float tstep = PI / 5.0;
    float radius = 20;
    if (wire)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_POLYGON);

    float mat_dif[] = { 1 , 1 , 0 };
    float mat_amb[] = { 0 , 0 , 0 };
    float mat_spec[] = { 0 , 0 , 0 };
    float mat_emmis[] = { 1 , 1 , 0 };
    float shininess = 0 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //glColor3f(1.0, 1.0, 0.0); // ЦВЕТ ЗВЕЗДЫ
    glVertex3f(x, y, z);
    for (size_t i = 0; i < 11; i++)
    {
        glVertex3f(x + sin(t) * radius, y, z + cos(t) * radius);
        t += tstep;
        if (radius == 20) radius = 10;
        else radius = 20;
    }
    glEnd();
}

void addTreeBalls()
{
    glTranslatef(0, 0, -75);
    glPushMatrix();
    addCycleOFBalls(25);
    glPopMatrix();

    glTranslatef(0, 0, 50);
    glPushMatrix();
    glRotatef(120, 0.0, 0.0, 1.0);
    addCycleOFBalls(20);
    glPopMatrix();

    glTranslatef(0, 0, 50);
    glPushMatrix();
    glRotatef(-120, 0.0, 0.0, 1.0);
    addCycleOFBalls(15);
    glPopMatrix();
}

void addGarland(float off, float height)
{
    glPushMatrix();

    float mat_dif[] = { 1 , 0 , 1 };
    float mat_amb[] = { 0 , 0 , 0 };
    float mat_spec[] = { 1 , 1 , 1 };
    //float mat_emmis[] = { 1 , 0 , 1 };
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    if (ligth_toggle)
    {
        float new_mat_emmis[] = { 1 , 0 , 1 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);
    }

    //glColor3f(1, 0, 1); // ЦВЕТ ГИРЛЯНДЫ

    int cnt = 12;
    float cur_off = off;
    float off_step = cur_off / (2 * cnt * 1.0);
    float z_step = height / (2 * cnt * 1.0);
    float angle = 360 / (cnt * 1.0);
    for (size_t i = 0; i < cnt; i++)
    {
        addBall(3, cur_off, false);
        cur_off -= off_step;
        glRotatef(angle, 0.0, 0.0, 1.0);
        glTranslatef(0, 0, z_step);
    }

    float new_mat_emmis[] = { 0 , 0 , 0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPopMatrix();
}

void addTree()
{
    glPushMatrix();
    glRotatef(tree_rot, 0.0, 0.0, 1.0);

    float mat_dif[] = { 150 / 255.0, 65 / 255.0, 20 / 255.0 };
    float mat_amb[] = { 0.5 , 0.5 , 0.5 };
    float mat_spec[] = { 1 , 1 , 1 };
    float shininess = 1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //glColor3f(150 / 255.0, 65 / 255.0, 20 / 255.0);

    if (wire)
        glutWireCylinder(10, 25, 12, 1);
    else
        glutSolidCylinder(10, 25, 12, 1);

    glTranslatef(0, 0, 25);

    addCone(50, 100);
    addGarland(35, 100);
    glTranslatef(0, 0, 50);
    addCone(40, 80);
    addGarland(27, 90);
    glTranslatef(0, 0, 50);
    addCone(30, 60);
    addGarland(20, 70);

    addTreeBalls();

    glTranslatef(0, 0, 45);
    addStar();
    glPopMatrix();
}

void loadTextures()
{
    floorTexture = SOIL_load_OGL_texture("floor_148.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ballTexture = SOIL_load_OGL_texture("glitter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void addFloor(int x, int y, int z, int size)
{
    glBindTexture(GL_TEXTURE_2D, floorTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(x + size, y + size, z);
    glTexCoord2f(0.0, 30.0); glVertex3f(x + size, y - size, z);
    glTexCoord2f(30.0, 30.0); glVertex3f(x - size, y - size, z);
    glTexCoord2f(30.0, 0.0); glVertex3f(x - size, y + size, z);
    glEnd();

    GLUquadricObj* quadObj;
    quadObj = gluNewQuadric();

    glDisable(GL_TEXTURE_2D);
}

void addPole()
{
    glPushMatrix();

    float mat_dif[] = { 0.4, 0.4, 0.4 };
    float mat_amb[] = { 0.3 , 0.3 , 0.23 };
    float mat_spec[] = { 1 , 1 , 1 };
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glColor3f(0.4, 0.4, 0.4); // ЦВЕТ СТОЛБА

    glutSolidCylinder(8, 20, 12, 1);
    glTranslatef(0, 0, 20);
    glutSolidCylinder(4, 150, 12, 1);
    glTranslatef(0, 0, 150);
    glutSolidCylinder(8, 4, 12, 1);
    glTranslatef(0, 0, 4);

    if (ligth_toggle)
    {
        float mat_emmis[] = { 250 / 255.0, 255 / 255.0, 150 / 255.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);
    }

    float new_mat_dif_1[] = { 250 / 255.0, 255 / 255.0, 150 / 255.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new_mat_dif_1);

    glutSolidCylinder(7, 10, 12, 1);
    glTranslatef(0, 0, 25);

    glTranslatef(0, 0, -20);

    float mat_emmis[] = { 0, 0, 0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);

    float new_mat_dif_2[] = { 0.4, 0.4, 0.4 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new_mat_dif_2);
    glutSolidCone(20, 20, 12, 1);

    glPopMatrix();
}

void addPoles()
{
    glTranslatef(160, 0, 0);
    addPole();
    glTranslatef(-320, 0, 0);
    addPole();
    glTranslatef(0, 320, 0);
    addPole();
    glTranslatef(320, 0, 0);
    addPole();
    glTranslatef(0, 320, 0);
    addPole();
    glTranslatef(-320, 0, 0);
    addPole();
}

void addStreet()
{
    glPushMatrix();

    auto m = getCoords();
    addFloor(get<0>(m), get<1>(m), get<2>(m), 2000);

    addPoles();

    glPopMatrix();
}

void addCar()
{
    glPushMatrix();

    float carCol[3]{ 255 / 255.0, 0 / 255.0, 0 / 255.0 };  // КОРПУС
    float glassCol[3]{ 120 / 255.0, 120 / 255.0, 120 / 255.0 }; // СТЕКЛО
    float wheelCol[3]{ 30 / 255.0, 30 / 255.0, 30 / 255.0 }; // КОЛЁСА
    float LightCol[3]{ 250 / 255.0, 190 / 255.0, 60 / 255.0 }; // ФАРЫ

    float mat_amb[] = { 0.5 , 0.5 , 0.5 };
    float mat_spec[] = { 0.5 , 0.5 , 0.5 };
    float mat_emmis[] = { 0 , 0 , 0 };
    float shininess = 0.1 * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, carCol);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmis);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glTranslatef(250, 400, 50); // СМЕЩЕНИЕ МАШИНЫ

    glRotatef(15, 0, 0, 1); // ПОВОРОТ МАШИНЫ

    glutSolidCube(50);
    glTranslatef(50, 0, 0);
    glutSolidCube(50);
    glTranslatef(25, 0, 25);


    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glassCol);

    glRotatef(45, 0, 1, 0);
    glutSolidCube(48);
    glRotatef(-45, 0, 1, 0);
    glTranslatef(50, 0, 0);
    glRotatef(45, 0, 1, 0);
    glutSolidCube(48);
    glRotatef(-45, 0, 1, 0);
    glTranslatef(-25, 0, 12);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, carCol);

    //glColor3f(carCol[0], carCol[1], carCol[2]);
    glutSolidCube(49);
    glTranslatef(0, 0, -37);
    glutSolidCube(50);
    glTranslatef(50, 0, 0);
    glutSolidCube(50);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wheelCol);

    glTranslatef(-150, 30, -25);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(25, 15, 12, 1);
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, -45, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(25, 15, 12, 1);
    glRotatef(-90, 1, 0, 0);

    glTranslatef(150, 45, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(25, 15, 12, 1);
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, -45, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(25, 15, 12, 1);
    glRotatef(-90, 1, 0, 0);

    if (ligth_toggle)
    {
        float new_mat_emmis[] = { 250 / 255.0, 190 / 255.0, 60 / 255.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LightCol);

    glTranslatef(-175, 30, 40);
    glutSolidSphere(10, 12, 12);
    glTranslatef(0, -30, 0);
    glutSolidSphere(10, 12, 12);

    float new_mat_emmis[] = { 0, 0, 0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);

    glPopMatrix();
}

void renderScene()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(rotate_x - 90, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -75);

    addStreet();

    addTree();

    addCar();

    glEnable(GL_LIGHTING);
    GLfloat light0dir[] = { 0 , 0, -1 };
    GLfloat light0loc[] = { 0 , -100, 500, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0loc);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0dir);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);

    glColor3f(1, 1, 1);

    glEnable(GL_LIGHT0);

    glFlush();
    glutSwapBuffers();
}

void Update()
{
    tree_rot += 1;
    renderScene();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow(" OpenGL_HelloWolrd ");

    glClearColor(0.2f, 0.4f, 0.5f, 1.0f);

    loadTextures();
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    wire = 0;
    tree_rot = 0;

    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(Reshape);
    glutDisplayFunc(renderScene);
    glutIdleFunc(Update);
    glutSpecialFunc(specialKeys);
    glutMainLoop();

    return 0;
}