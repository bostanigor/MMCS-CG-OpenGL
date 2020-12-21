#pragma once
#ifndef OPENGLABS_COMMON_H
#define OPENGLABS_COMMON_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

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
    GLint vSuccess = 0;
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vSuccess);

    if (vSuccess == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vShader, maxLength, &maxLength, &errorLog[0]);

//        std::cout << "Vertex shader error: ";
        for (auto symbol : errorLog)
            std::cout << symbol;
    }

    //! ??????? ??????????? ??????
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //! ???????? ???????? ???
    glShaderSource(fShader, 1, &fsSource, NULL);
    //! ??????????? ??????
    glCompileShader(fShader);

    GLint fSuccess = 0;
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &fSuccess);

    if (fSuccess == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vShader, maxLength, &maxLength, &errorLog[0]);

//        std::cout << "Fragment shader error: ";
        for (auto symbol : errorLog)
            std::cout << symbol;
    }

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

    virtual void special(int key) = 0;
    virtual void update() = 0;
    virtual void render() const = 0;
};

struct vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct vec4 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
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

struct UniformStruct {
    std::string name;
    GLuint program;
    std::map<std::string, GLuint> data;

    UniformStruct() {}

    UniformStruct(std::string name, std::vector<std::string> fields, GLuint program) {
        this->name = name;
        this->program = program;
        for (auto field : fields) {
            data[field] = getUniformId(name + "." + field, program);
        }
    }

    GLuint get(std::string field) {
        return data[field];
    }
};

struct Light {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 attenuation;

    Light() {}

    Light(vec4 position, vec4 ambient, vec4 diffuse, vec4 specular, vec3 attenuation)
    : position(position), ambient(ambient), diffuse(diffuse), specular(specular), attenuation(attenuation) {}

public:
    void setUniform(UniformStruct uniform) const {
        glUniform4f(uniform.get("position"), position.x, position.y, position.z, position.w);
        glUniform4f(uniform.get("ambient"), ambient.x, ambient.y, ambient.z, ambient.w);
        glUniform4f(uniform.get("diffuse"), diffuse.x, diffuse.y, diffuse.z, diffuse.w);
        glUniform4f(uniform.get("specular"), specular.x, specular.y, specular.z, specular.w);
        glUniform3f(uniform.get("attenuation"), attenuation.x, attenuation.y, attenuation.z);
    }
};

struct Material {
    GLuint texture;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emission;
    float shininess;

    Material() {}

    Material(GLuint texture, vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess)
        : texture(texture), ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), shininess(shininess) {}

public:
    void setUniform(UniformStruct uniform) const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform4f(uniform.get("ambient"), ambient.x, ambient.y, ambient.z, ambient.w);
        glUniform4f(uniform.get("diffuse"), diffuse.x, diffuse.y, diffuse.z, diffuse.w);
        glUniform4f(uniform.get("specular"), specular.x, specular.y, specular.z, specular.w);
        glUniform4f(uniform.get("emission"), emission.x, emission.y, emission.z, emission.w);
        glUniform1f(uniform.get("shininess"), shininess);
    }
};

struct mat4 {
    float data[16];
};

struct mat3 {
    float data[9];
};

struct Transform {
    mat4 model;
    mat4 viewProjection;
    mat3 normal;
    vec3 viewPosition;

public:
    void setUniform(UniformStruct uniform) const {
        glUniformMatrix4fv(uniform.get("model"), 1, GL_FALSE, &model.data[0]);
        glUniformMatrix4fv(uniform.get("viewProjection"), 1, GL_FALSE, &viewProjection.data[0]);
        glUniformMatrix3fv(uniform.get("normal"), 1, GL_FALSE, &normal.data[0]);
        glUniform3f(uniform.get("viewPosition"), viewPosition.x, viewPosition.y, viewPosition.z);
    }
};


#endif //OPENGLABS_COMMON_H
