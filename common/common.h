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
extern std::string ltrim(const std::string& s);
extern std::string readFile(const std::string &filePath);
extern std::vector<std::string> split(const std::string &str, const std::string &delim = " ");

extern GLint getAttributeId(const std::string &attributeName, GLint program);
extern GLint getUniformId(const std::string &uniformName, GLint program);

extern GLint initShaderProgram(const std::string &vsPath, const std::string &fsPath);

extern GLuint loadTex(const std::string &filePath);

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

    vec3 operator-() {
        return { -x, -y, -z };
    }
};

struct vec2 {
    GLfloat x;
    GLfloat y;
};

struct UniformStruct {
    std::string name;

    //! Program -> (uniform name -> uniform id)
    std::map<GLuint, std::map<std::string, GLuint>> data;

    UniformStruct() {}

    UniformStruct(std::string name, std::vector<std::string> fields, std::vector<GLuint> programs) {
        this->name = name;
        for (auto program : programs) {
            data[program] = std::map<std::string, GLuint>();
            glUseProgram(program);
            for (auto field : fields) {
                data[program][field] = getUniformId(name + "." + field, program);
            }
        }
    }

    GLuint get(GLuint program, std::string field) {
        return data[program][field];
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
    void setUniform(GLuint program, UniformStruct uniform) const {
        glUniform4f(uniform.get(program, "position"), position.x, position.y, position.z, position.w);
        glUniform4f(uniform.get(program, "ambient"), ambient.x, ambient.y, ambient.z, ambient.w);
        glUniform4f(uniform.get(program, "diffuse"), diffuse.x, diffuse.y, diffuse.z, diffuse.w);
        glUniform4f(uniform.get(program, "specular"), specular.x, specular.y, specular.z, specular.w);
        glUniform3f(uniform.get(program, "attenuation"), attenuation.x, attenuation.y, attenuation.z);
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
    void setUniform(GLuint program, UniformStruct uniform) const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform4f(uniform.get(program, "ambient"), ambient.x, ambient.y, ambient.z, ambient.w);
        glUniform4f(uniform.get(program, "diffuse"), diffuse.x, diffuse.y, diffuse.z, diffuse.w);
        glUniform4f(uniform.get(program, "specular"), specular.x, specular.y, specular.z, specular.w);
        glUniform4f(uniform.get(program, "emission"), emission.x, emission.y, emission.z, emission.w);
        glUniform1f(uniform.get(program, "shininess"), shininess);
    }
};

struct mat4 {
    float data[16];

    mat4 operator *(const mat4 &other) {
        mat4 result = { 0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f};
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    result.data[i * 4 + j] += data[i * 4 + k] * other.data[k * 4 + j];

        return result;
    }

    vec4 operator *(const vec4 &vert) {
        float result[4] = { 0.0f, 0.0f, 0.0f };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                result[i] = data[i * 4 + 0] * vert.x +
                        data[i * 4 + 1] * vert.y +
                        data[i * 4 + 2] * vert.z +
                        data[i * 4 + 3] * vert.w;
            }
        return vec4 { result[0], result[1], result[2], result[3] };
    }
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
    void setUniform(GLuint program, UniformStruct uniform) const {
        glUniformMatrix4fv(uniform.get(program, "model"), 1, GL_FALSE, &model.data[0]);
        glUniformMatrix4fv(uniform.get(program, "viewProjection"), 1, GL_FALSE, &viewProjection.data[0]);
        glUniformMatrix3fv(uniform.get(program, "normal"), 1, GL_FALSE, &normal.data[0]);
        glUniform3f(uniform.get(program, "viewPosition"), viewPosition.x, viewPosition.y, viewPosition.z);
    }
};

static mat4 rotationYMatrix(float angle) {
    return {
            cos(angle), 0.0, sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(angle), 0.0, cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

static mat4 offsetMatrix(vec3 position) {
   return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            position.x, position.y, position.z, 1.0f,
    };
}

#endif //OPENGLABS_COMMON_H
