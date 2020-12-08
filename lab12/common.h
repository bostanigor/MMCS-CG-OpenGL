#ifndef OPENGLABS_COMMON_H
#define OPENGLABS_COMMON_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <fstream>

//! �������� ������ OpenGL, ���� ���� �� ����� � ������� ��� ������
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

//! ������������� ��������
GLint initShaderProgram(const std::string &vsPath, const std::string &fsPath)
{
    //! �������� ��� ��������
    auto vsSourceCode = readFile(vsPath);
    auto fsSourceCode = readFile(fsPath);
    const char* vsSource = vsSourceCode.c_str();
    const char* fsSource = fsSourceCode.c_str();

    //! ���������� ��� �������� ��������������� ��������
    GLuint vShader, fShader;
    //! ������� ��������� ������
    vShader = glCreateShader(GL_VERTEX_SHADER);
    //! �������� �������� ���
    glShaderSource(vShader, 1, &vsSource, NULL);
    //! ����������� ������
    glCompileShader(vShader);
    //! ������� ����������� ������
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //! �������� �������� ���
    glShaderSource(fShader, 1, &fsSource, NULL);
    //! ����������� ������
    glCompileShader(fShader);
    //! ������� ��������� � ����������� ������� � ���
    auto program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    //! ������� ��������� ���������
    glLinkProgram(program);
    //! ��������� ������ ������
    int link_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
        throw std::exception("error attach shaders");

    return program;

//    checkOpenGLerror();
}

class task {
protected:
    GLuint program;

public:
    GLuint getProgram() const {
        return program;
    }

    virtual void update() = 0;
    virtual void render() const = 0;
};

struct vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

#endif //OPENGLABS_COMMON_H
