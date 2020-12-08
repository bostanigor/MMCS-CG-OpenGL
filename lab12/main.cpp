#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

auto tasks = new task*[5];
task * currentTask;
GLuint currentShader;

bool shadersActive = true;

void update() {
    currentTask->update();
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
    currentTask = tasks[0];
    currentShader = currentTask->getProgram();
    glUseProgram(currentShader);
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
    freeShaders();
}