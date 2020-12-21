#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/model3D.h"
#include "./task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include <iostream>

auto tasks = new task*[5];
task * currentTask;
GLuint currentShader;

bool shadersActive = true;

void update() {
    currentTask->update();
}

void render() {
    currentTask->render();
}

void specialKeys(int key, int x, int y) {
    auto offset = key - GLUT_KEY_F1;

    //! Если нажали F1-F5 - переключаем задачу
    if (offset >= 0 && offset < 5) {
        currentTask = tasks[offset];
        currentShader = currentTask->getProgram();
    }
        //! Если нажали F6 - вырубаем шейдер
    else if (offset == 5)
        shadersActive = !shadersActive;

    if (shadersActive)
        glUseProgram(currentShader);
    else
        glUseProgram(0);

    glutPostRedisplay();
}

//! Освобождение шейдеров
void freeShaders()
{
    //! Передавая ноль, мы отключаем шейдрную программу
    glUseProgram(0);
    //! Удаляем шейдерную программу
    for (int i = 0; i < 5; i++) {
        glDeleteProgram(tasks[i]->getProgram());
    }
}
void resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
}

void initTasks() {
    tasks[0] = new task1();
    tasks[1] = new task2();
    tasks[2] = new task3();
    tasks[3] = new task4();
    tasks[4] = new task5();
    currentTask = tasks[0];
    currentShader = currentTask->getProgram();
    glUseProgram(currentShader);
}

void computeNormal(float * coords) {
    float x0 = coords[0];
    float y0 = coords[1];
    float z0 = coords[2];
    float x1 = coords[3];
    float y1 = coords[4];
    float z1 = coords[5];
    float x2 = coords[6];
    float y2 = coords[7];
    float z2 = coords[8];

    std::cout << "A: " << (y1 - y0) * (z2- z0) - (z1 - z0)* (y2 - y0) << std::endl;
    std:: cout << "B: " << (z1 - z0) * (x2 - x0) - (x1 - x0) * (z2 -z0) << std::endl;
    std:: cout << "C: " << (x1- x0)* (y2 - y0) - (y1 - y0) * (x2 - x0) << std::endl;
}

int main(int argc, char **argv)
{
    float a[] = {-0.5f, -0.5f, -0.5f,
                 -0.5f, 0.5f, -0.5f,
                 0.5f, 0.5f, -0.5f};
    computeNormal(a);
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
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    //! Освобождение ресурсов
    freeShaders();
}