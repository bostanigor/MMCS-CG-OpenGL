#ifndef OPENGLABS_TASK1_H
#define OPENGLABS_TASK1_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "../common/common.h"
#include "../common/stb_image.h"

class task1 : public task {
    GLuint uniformAngle;
    GLuint texture;

    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;

public:
    task1() {
        program = initShaderProgram("../shaders/lab13/cube_textured.vs.c",
                                    "../shaders/lab13/cube_textured_mix_color.fs.c");
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../assets/glitter.jpg", &width, &height, &nrChannels, 0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        uniformAngle = getUniformId("angle", program);
        initVBO();
        initVAO();
        initEBO();
    }

    void update() override {
        rotate_x += 0.1;
        rotate_y += 0.1;
        rotate_z += 0.1;
        render();
    }

    void initVBO() {
        float vertices[] = {
                // coordinates          colors              tex coords
                -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0,
                -0.5f,  0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                 0.5f,  0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
                 0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0,
                -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        };

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    void initVAO() {
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);
    }

    void initEBO() {
        unsigned int indices[] = {  // note that we start from 0!
                /*0, 1, 2, 3,
                3, 2, 6, 7,
                7, 6, 5, 4,
                4, 5, 1, 0,
                1, 5, 6, 2,
                0, 3, 7, 4,*/
                3, 2, 1, 0,
                7, 6, 2, 3,
                4, 5, 6, 7,
                0, 1, 5, 4,
                2, 6, 5, 1,
                4, 7, 3, 0,
        };

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        double pi = 3.1415926535897932;
        glUniform3f(uniformAngle,
                    (GLfloat)(rotate_x * pi / 180),
                    (GLfloat)(rotate_y * pi / 180),
                    (GLfloat)(rotate_z * pi / 180));

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glFlush();

        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK1_H
