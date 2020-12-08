#ifndef OPENGLABS_COMMON_H
#define OPENGLABS_COMMON_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <fstream>

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

std::string readFile(const std::string &filePath) {
    std::string line, text;
    std::ifstream in(filePath);
    while(std::getline(in, line))
        text += ltrim(line) + "\n";
    return text;
}

GLint getAttributeId(const std::string &attributeName, GLint program) {
    const char* attr_name = attributeName.c_str();
    auto result = glGetAttribLocation(program, attr_name);

    if (result == -1)
        throw std::exception("could not bind attribute");

    return result;
}

GLint getUniformId(const std::string &uniformName, GLint program) {
    const char* unif_name = uniformName.c_str();
    auto result = glGetUniformLocation(program, unif_name);

    if (result == -1)
        throw std::exception("could not bind uniform");

    return result;
}

//! Инициализация шейдеров
GLint initShaderProgram(const std::string &vsPath, const std::string &fsPath)
{
    //! Исходный код шейдеров
    auto vsSourceCode = readFile(vsPath);
    auto fsSourceCode = readFile(fsPath);
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
    auto program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    //! Линкуем шейдерную программу
    glLinkProgram(program);
    //! Проверяем статус сборки
    int link_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
        throw std::exception("error attach shaders");

    return program;

    checkOpenGLerror();
}

#endif //OPENGLABS_COMMON_H
