#include "model.h"


std::vector<std::string> model::splitPolygon(std::vector<std::string> &words) {
    std::vector<std::string> result;
    //! start from 2 because we skip first word 'f'
    for (int i = 2; i < words.size(); i++) {
        result.emplace_back(words[1]);
        result.emplace_back(words[2]);
        result.emplace_back(words[3]);
    }
    return result;
}

void model::parseFile(const std::string &filePath) {
    std::string line;
    std::ifstream in(filePath);

    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<vec2> texCoords;
    std::vector<float> result;

    while(std::getline(in, line)) {
        auto words = split(line);
        if (words[0] == "v") {
            vertices.push_back({
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
                    auto vertex = vertices[vertexInd - 1];
                    result.emplace_back(vertex.x);
                    result.emplace_back(vertex.y);
                    result.emplace_back(vertex.z);
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
                if (!indicies[2].empty()) {
                    auto normalInd = std::stoi(indicies[2]);
                    auto normal = normals[normalInd - 1];
                    result.emplace_back(normal.x);
                    result.emplace_back(normal.y);
                    result.emplace_back(normal.z);
                }
                else {
                    result.emplace_back(0.0f);
                    result.emplace_back(0.0f);
                }
            }
        }
    }
    verticesData = result;
}

void model::initVBO() {
    auto data = verticesData.data();
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void model::initVAO() {
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

model::model(const std::string &filePath) {
    parseFile(filePath);
    initVBO();
    initVAO();
}

