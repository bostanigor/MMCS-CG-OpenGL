#include <iostream>
#define GL_SILENCE_DEPRECATION
///Freeglut
#include <GL/freeglut.h>
///Apple's GLUT
//#include <GLUT/glut.h>
using namespace std;


double rotate_x =0;
double rotate_y =0;
double rotate_z =0;


void renderRectangle()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0, 1.0, 0.0);    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0, 0.0, 1.0);    glVertex2f(0.5f, 0.5f);
    glColor3f(1.0, 1.0, 1.0);    glVertex2f(0.5f, -0.5f);
    glEnd();
    glFlush();
}

void renderWireCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glutWireCube(1);
    glFlush();
}

//Глобальные статические переменные -
//хранят текущий размер экрана
static int w = 0 , h = 0 ;
//Функция вызываемая перед вхождением в главный цикл
void Init () {
    glClearColor( 0.0f,0.0f,0.0f,1.0f) ;
}
//Функция вызываемая каждый кадр -
// для его отрисовки, вычислений и т. д.
void Update () {
    glClear(GL_COLOR_BUFFER_BIT) ;
//    renderRectangle();
    renderWireCube();
    glutSwapBuffers() ;
}
//Функця вызываемая при изменении размеров окна
void Reshape(int width , int height) {
w = width ; h = height ;
}


int main(int argc, char* argv [])
{
    //Инициализировать сам glut
    glutInit(&argc, argv);
    //Установить начальное положение окна
    glutInitWindowPosition(100,100);
    //Установить начальные размеры окна
    glutInitWindowSize(800,600);
    //Установить параметры окна - двойная буфферизация
    // и поддержка цвета RGBA

    ///Apple's GLUT
//    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE);

    ///Freeglut
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitContextVersion ( 3, 2);
    glutInitContextFlags   ( GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG );
    glutInitContextProfile ( GLUT_CORE_PROFILE );

    //Создать окно с заголовком OpenGL
    glutCreateWindow("OpenGL");


    //Укажем glut функцию, которая будет вызываться каждый кадр
    glutIdleFunc(Update);
    //Укажем glut функцию, которая будет рисовать каждый кадр
    glutDisplayFunc( Update );
    //Укажем glut функцию, которая будет вызываться при
    // изменении размера окна приложения
    glutReshapeFunc(Reshape);
    Init() ;

    printf("GL_VERSION = %s\n",glGetString(GL_VERSION) );

    //Войти в главный цикл приложения
    glutMainLoop();
    return 0;
}
