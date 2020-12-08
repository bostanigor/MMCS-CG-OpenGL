#include "GL/glew.h"
#include "GL/freeglut.h"
#include "common.h"
#include "task1.h"

task1 *t1;

void task1update() { t1->update(); }

//! Освобождение шейдеров
void freeShader()
{
//! Передавая ноль, мы отключаем шейдрную программу
    glUseProgram(0);
//! Удаляем шейдерную программу
//    glDeleteProgram(t1.getProgram());
}
void resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
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
    t1 = new task1();
//    initShader();
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(task1update);
    glutIdleFunc(task1update);
    glutMainLoop();
    //! Освобождение ресурсов
    freeShader();
}