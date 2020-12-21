#ifndef OPENGLABS_MODEL3D_H
#define OPENGLABS_MODEL3D_H

#include "common.h"
#include <vector>

class model3D {
    std::vector<float> verticesData;
    GLfloat * vertices;

public:
    GLuint VAO;
    GLuint VBO;
    int polygonCount;
    int elementCount;

    model3D(const std::string &filePath, float scale);

private:
    //! To split faces with more than 3 vertices
    std::vector<std::string> splitPolygon(std::vector<std::string> &words);

    void parseFile(const std::string &filePath, float scale);

    void initVBO();
    void initVAO();
};

#endif //OPENGLABS_MODEL3D_H
