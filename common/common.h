#pragma once
#ifndef OPENGLABS_COMMON_H
#define OPENGLABS_COMMON_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

static void checkOpenGLerror()
{
    GLenum errCode;
    if ((errCode = glGetError()) != GL_NO_ERROR)
        std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

static const std::string WHITESPACE = " \n\r\t\f\v";
static std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

static std::string readFile(const std::string &filePath) {
    std::string line, text;
    std::ifstream in(filePath);
    while(std::getline(in, line))
        text += ltrim(line) + "\n";
    return text;
}

static std::vector<std::string> split(const std::string &str, const std::string &delim = " ") {
    std::vector<std::string> result;
    size_t last = 0;
    size_t next = 0;
    while ((next = str.find(delim, last)) != std::string::npos) {
        result.emplace_back(str.substr(last, next - last));
        last = next + 1;
    }
    result.emplace_back(str.substr(last));
    return result;
}

static GLint getAttributeId(const std::string &attributeName, GLint program) {
    const char* attr_name = attributeName.c_str();
    auto result = glGetAttribLocation(program, attr_name);

    if (result == -1)
        throw std::exception("could not bind attribute");

    return result;
}

static GLint getUniformId(const std::string &uniformName, GLint program) {
    const char* unif_name = uniformName.c_str();
    auto result = glGetUniformLocation(program, unif_name);

    if (result == -1)
        throw std::exception("could not bind uniform");

    return result;
}

static GLint initShaderProgram(const std::string &vsPath, const std::string &fsPath)
{
    //! ???????? ??? ????????
    auto vsSourceCode = readFile(vsPath);
    auto fsSourceCode = readFile(fsPath);
    const char* vsSource = vsSourceCode.c_str();
    const char* fsSource = fsSourceCode.c_str();

    //! ?????????? ??? ???????? ??????????????? ????????
    GLuint vShader, fShader;
    //! ??????? ????????? ??????
    vShader = glCreateShader(GL_VERTEX_SHADER);
    //! ???????? ???????? ???
    glShaderSource(vShader, 1, &vsSource, NULL);
    //! ??????????? ??????
    glCompileShader(vShader);
    GLint success = 0;
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);

    //! ??????? ??????????? ??????
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //! ???????? ???????? ???
    glShaderSource(fShader, 1, &fsSource, NULL);
    //! ??????????? ??????
    glCompileShader(fShader);
    //! ??????? ????????? ? ??????????? ??????? ? ???
    auto program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    //! ??????? ????????? ?????????
    glLinkProgram(program);
    //! ????????? ?????? ??????
    int link_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);

    if (link_ok == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        for (auto symbol : infoLog)
            std::cout << symbol;
    }

    checkOpenGLerror();

    return program;
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

struct vec3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct vec2 {
    GLfloat x;
    GLfloat y;
};

#endif //OPENGLABS_COMMON_H
