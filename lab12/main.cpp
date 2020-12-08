#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common.h"
#include "task1.h"

task1 *t1;

int activeTask = 1;
int currentShaderProgram;
bool shadersActive = true;


void update() {
    switch(activeTask) {
        case 1: t1->update(); break;
        default: break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            activeTask = 1;
            currentShaderProgram = t1->getProgram();
            break;
        case GLUT_KEY_F2:
            activeTask = 2;
            break;
        case GLUT_KEY_F3:
            activeTask = 3;
            break;
        case GLUT_KEY_F4:
            activeTask = 4;
            break;
        case GLUT_KEY_F5:
            activeTask = 5;
            break;
        case GLUT_KEY_F6:
            if (shadersActive)
                glUseProgram(0);
            else
                glUseProgram(currentShaderProgram);
            shadersActive = !shadersActive;
            break;
    }
    glutPostRedisplay();
}

//! Освобождение шейдеров
void freeShader()
{
//! Передавая ноль, мы отключаем шейдрную программу
    glUseProgram(0);
//! Удаляем шейдерную программу
    glDeleteProgram(t1->getProgram());
}
void resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
}

void initTasks() {
    t1 = new task1();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple shaders");
    glClearColor(0, 0, 0, 0);
    //! Обязательно перед инициализацией шейдеров
    GLenum glew_status = glewInit();
    if (GLEW_OK != glew_status)
    {
        //! GLEW не проинициализировалась
        std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
        return 1;
    }
    //! Проверяем доступность OpenGL 2.0
    if (!GLEW_VERSION_2_0)
    {
        //! OpenGl 2.0 оказалась не доступна
        std::cout << "No support for OpenGL 2.0 found\n";
        return 1;
    }
    //! Инициализация шейдеров
    initTasks();
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(update);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    //! Освобождение ресурсов
    freeShader();
}