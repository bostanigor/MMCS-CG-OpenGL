#include "common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string readFile(const std::string &filePath) {
    std::string line, text;
    std::ifstream in(filePath);
    while(std::getline(in, line))
        text += ltrim(line) + "\n";
    return text;
}

std::vector<std::string> split(const std::string &str, const std::string &delim) {
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

GLint getAttributeId(const std::string &attributeName, GLint program) {
    const char* attr_name = attributeName.c_str();
    auto result = glGetAttribLocation(program, attr_name);

    if (result == -1)
        throw std::exception("could not bind attribute");

    return result;
}

GLint getUniformId(const std::string &uniformName, GLint program) {
    const char* unif_name = uniformName.c_str();
    auto result = glGetUniformLocation(program, unif_name);

    /*if (result == -1)
        throw std::exception("could not bind uniform");*/

    return result;
}

GLint initShaderProgram(const std::string &vsPath, const std::string &fsPath) {
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

GLuint loadTex(const std::string &filePath) {
    GLuint texture;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
