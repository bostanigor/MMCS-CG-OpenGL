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
                                    "../shaders/lab13/cube_textured.fs.c");
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../assets/earth-texture.jpg", &width, &height, &nrChannels, 0);


        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        uniformAngle = getUniformId("angle", program);
        initVBO();
        initEBO();
        initVAO();
    }

    void update() override {
        rotate_z += 1.0;
        rotate_x += 1.0;
//        rotate_z += 0.1;
        render();
    }

    void initVBO() {
        float vertices[] = {
                // coordinates          colors              tex coords
                -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,   0.34f, 0.51f,  // 0
                -0.5f,  0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   0.34f, 0.74f,  // 1
                 0.5f,  0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   0.66f, 0.74f,  // 2
                 0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   0.66f, 0.51f,  // 3

                -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.34f, 0.25f, // 4
                -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.34f, 0.0f,  // 5
                 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.66f, 0.0f,  // 6
                 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,   0.66f, 0.25f, // 7

                -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.51f, // 8(4)
                -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.74f, // 9(5)
                 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.74f, // 10(6)
                 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,   1.0f, 0.51f, // 11(7)

                -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.34f, 1.0f, // 12(5)
                 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.66f, 1.0f, // 13(6)
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
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBindVertexArray(0);
    }

    void initEBO() {
        unsigned int indices[] = {  // note that we start from 0!
                0, 1, 2, 3,
                0, 3, 7, 4,
                4, 7, 6, 5,
                1, 12, 13, 2,
                9, 1, 0, 8,
                2, 10, 11, 3,
        };

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);

        double pi = 3.1415926535897932;
        glUniform3f(uniformAngle,
                    (GLfloat)(rotate_x * pi / 180),
                    (GLfloat)(rotate_y * pi / 180),
                    (GLfloat)(rotate_z * pi / 180));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glFlush();

        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK1_H
