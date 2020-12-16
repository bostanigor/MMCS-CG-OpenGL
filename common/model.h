#ifndef OPENGLABS_MODEL_H
#define OPENGLABS_MODEL_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <string>
#include <fstream>
#include <vector>
#include "../common/common.h"

class model {
    GLuint VAO;
    GLuint VBO;

    std::vector<float> verticesData;

public:
    model(const std::string &filePath);

private:
    //! To split faces with more than 3 vertices
    std::vector<std::string> splitPolygon(std::vector<std::string> &words);

    void parseFile(const std::string &filePath);

    void initVBO();
    void initVAO();
};

#endif //OPENGLABS_MODEL_H
