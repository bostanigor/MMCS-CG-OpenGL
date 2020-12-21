#include "model3D.h"


std::vector<std::string> model3D::splitPolygon(std::vector<std::string> &words) {
    std::vector<std::string> result;
    //! start from 2 because we skip first word 'f'
    for (int i = 2; i < words.size() - 1; i++) {
        result.emplace_back(words[1]);
        result.emplace_back(words[i]);
        result.emplace_back(words[i + 1]);
    }
    return result;
}

void model3D::parseFile(const std::string &filePath, float scale = 1) {
    std::string line;
    std::ifstream in(filePath);

    std::vector<vec3> positions;
    std::vector<vec3> normals;
    std::vector<vec2> texCoords;
    std::vector<float> result;

    polygonCount = 0;
    while(std::getline(in, line)) {
        auto words = split(line);
        if (words[0] == "v") {
            positions.push_back({
                   std::stof(words[1]),
                   std::stof(words[2]),
                   std::stof(words[3]),
            });
        }
        else if (words[0] == "vn") {
            normals.push_back({
                  std::stof(words[1]),
                  std::stof(words[2]),
                  std::stof(words[3]),
            });
        }
        else if (words[0] == "vt") {
            texCoords.push_back({
                  std::stof(words[1]),
                  std::stof(words[2]),
            });
        }
        else if (words[0] == "f") {
            auto corteges = splitPolygon(words);
            for (const auto& cortege : corteges) {
                auto indicies = split(cortege, "/");
                if (!indicies[0].empty()) {
                    auto vertexInd = std::stoi(indicies[0]);
                    auto vertex = positions[vertexInd - 1];
                    result.emplace_back(vertex.x * scale);
                    result.emplace_back(vertex.y * scale);
                    result.emplace_back(vertex.z * scale);
                }
                if (!indicies[1].empty()) {
                    auto texCoordInd = std::stoi(indicies[1]);
                    auto texCoord = texCoords[texCoordInd - 1];
                    result.emplace_back(texCoord.x);
                    result.emplace_back(texCoord.y);
                }
                else {
                    result.emplace_back(0.0f);
                    result.emplace_back(0.0f);
                }
                if (indicies.size() > 2 && !indicies[2].empty()) {
                    auto normalInd = std::stoi(indicies[2]);
                    auto normal = normals[normalInd - 1];
                    result.emplace_back(normal.x);
                    result.emplace_back(normal.y);
                    result.emplace_back(normal.z);
                }
                else {
                    result.emplace_back(0.0f);
                    result.emplace_back(0.0f);
                    result.emplace_back(0.0f);
                }
                polygonCount++;
            }
        }
    }
    verticesData = result;
}

void model3D::initVBO() {
    vertices = verticesData.data();
    elementCount = verticesData.size();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, elementCount * sizeof(float), vertices, GL_STATIC_DRAW);
}

void model3D::initVAO() {
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //! Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        //! Texture coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        //! Normals
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glBindVertexArray(0);
}

model3D::model3D(const std::string &filePath, float scale = 1) {
    parseFile(filePath, scale);
    initVBO();
    initVAO();
}

