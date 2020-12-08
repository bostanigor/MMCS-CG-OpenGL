#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <fstream>

//! Переменные с индентификаторами ID
//! ID шейдерной программы
GLuint Program;
//! ID атрибута
GLint Attrib_vertex;
//! ID юниформ переменной цвета
GLint Unif_color;
GLint Unif_angle;

//! Проверка ошибок OpenGL, если есть то вывод в консоль тип ошибки
void checkOpenGLerror()
{
    GLenum errCode;
    if ((errCode = glGetError()) != GL_NO_ERROR)
        std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

const std::string WHITESPACE = " \n\r\t\f\v";
std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string readFile(std::string filePath) {
    std::string line, text;
    std::ifstream in(filePath);
    while(std::getline(in, line))
        text += ltrim(line) + "\n";
    return text;
}

GLint getAttributeId(std::string attribute_name) {
    const char* attr_name = attribute_name.c_str();
    auto result = glGetAttribLocation(Program, attr_name);

    if (Attrib_vertex == -1)
        throw std::exception("could not bind attribute");

    return result;
}

GLint getUniformId(std::string uniform_name) {
    const char* unif_name = uniform_name.c_str();
    auto result = glGetUniformLocation(Program, unif_name);

    if (Unif_color == -1)
        throw std::exception("could not bind uniform");

    return result;
}

//! Инициализация шейдеров
void initShader()
{
    //! Исходный код шейдеров
    auto vsSourceCode = readFile("../shaders/rotate_vertices_x.vs.c");
    auto fsSourceCode = readFile("../shaders/color_fragment.fs.c");
    const char* vsSource = vsSourceCode.c_str();
    const char* fsSource = fsSourceCode.c_str();

    //! Переменные для хранения идентификаторов шейдеров
    GLuint vShader, fShader;
    //! Создаем вершинный шейдер
    vShader = glCreateShader(GL_VERTEX_SHADER);
    //! Передаем исходный код
    glShaderSource(vShader, 1, &vsSource, NULL);
    //! Компилируем шейдер
    glCompileShader(vShader);
    //! Создаем фрагментный шейдер
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //! Передаем исходный код
    glShaderSource(fShader, 1, &fsSource, NULL);
    //! Компилируем шейдер
    glCompileShader(fShader);
    //! Создаем программу и прикрепляем шейдеры к ней
    Program = glCreateProgram();
    glAttachShader(Program, vShader);
    glAttachShader(Program, fShader);
    //! Линкуем шейдерную программу
    glLinkProgram(Program);
    //! Проверяем статус сборки
    int link_ok;
    glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
    {
        std::cout << "error attach shaders \n";
        return;
    }
    ///! Вытягиваем ID атрибута из собранной программы
    Attrib_vertex = getAttributeId("coord");

    //! Вытягиваем ID юниформ
//    Unif_color = getUniformId("color");
    Unif_angle = getUniformId("angle");
    checkOpenGLerror();
}
//! Освобождение шейдеров
void freeShader()
{
//! Передавая ноль, мы отключаем шейдрную программу
    glUseProgram(0);
//! Удаляем шейдерную программу
    glDeleteProgram(Program);
}
void resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
}

static float angle = 3.14 / 4;
//! Отрисовка
void render1()
{
    glClear(GL_COLOR_BUFFER_BIT);
//! Устанавливаем шейдерную программу текущей
    glUseProgram(Program);
    static float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
//! Передаем юниформ в шейдер
    glUniform1f(Unif_angle, angle);
//    glUniform4f(Unif_angle, 1, angle);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.0f);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.0f);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5f, 0.5f, 0.0f);
//    glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();

    glFlush();
//! Отключаем шейдерную программу
    glUseProgram(0);
    checkOpenGLerror();
    glutSwapBuffers();
}

void update() {
    angle += 0.1;
    render1();
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
    initShader();
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render1);
    glutIdleFunc(update);
    glutMainLoop();
//! Освобождение ресурсов
    freeShader();
}