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

    float angleVal;

public:
    task1() {
        program = initShaderProgram("../shaders/lab13/cube_textured.vs.c",
                                    "../shaders/lab13/cube_textured.fs.c");
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../assets/floor.jpg", &width, &height, &nrChannels, 0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        initVAO();

    }

    void update() override {
        angleVal += 0.1;
        render();
    }

    void initVAO() {
        float vertices[] = {
                // coordinates          colors              tex coords
                -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0,
                -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        };

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);


        glBindVertexArray(VAO);
        glDrawArrays(GL_QUADS, 0, 4);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glFlush();

        glutSwapBuffers();
    }
};

#endif //OPENGLABS_TASK1_H
