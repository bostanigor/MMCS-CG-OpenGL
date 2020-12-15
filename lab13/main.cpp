#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "./task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"

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

    //! ���� ������ F1-F5 - ����������� ������
    if (offset >= 0 && offset < 5) {
        currentTask = tasks[offset];
        currentShader = currentTask->getProgram();
    }
        //! ���� ������ F6 - �������� ������
    else if (offset == 5)
        shadersActive = !shadersActive;

    if (shadersActive)
        glUseProgram(currentShader);
    else
        glUseProgram(0);

    glutPostRedisplay();
}

//! ������������ ��������
void freeShaders()
{
    //! ��������� ����, �� ��������� �������� ���������
    glUseProgram(0);
    //! ������� ��������� ���������
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
    /*tasks[3] = new task4();
    tasks[4] = new task5();*/
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
    //! ����������� ����� �������������� ��������
    GLenum glew_status = glewInit();
    if (GLEW_OK != glew_status)
    {
        //! GLEW �� ���������������������
        std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
        return 1;
    }
    //! ��������� ����������� OpenGL 2.0
    if (!GLEW_VERSION_2_0)
    {
        //! OpenGl 2.0 ��������� �� ��������
        std::cout << "No support for OpenGL 2.0 found\n";
        return 1;
    }
    //! ������������� ��������
    initTasks();
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    //! ������������ ��������
    freeShaders();
}