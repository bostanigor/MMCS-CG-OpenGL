#ifndef OPENGLABS_TASK5_H
#define OPENGLABS_TASK5_H

class task5 : public task {
    GLuint uniformAngle;
    GLint attrib_vertex;
    GLint attrib_vertex_color;
    GLuint Vertex_VBO;
    GLuint Color_VBO;

    double rotate_x = 0;
    double rotate_y = 0;
    double rotate_z = 0;

public:
    task5() {
        initVBO();
        program = initShaderProgram("../shaders/cube_vbo.vs.c",
                                    "../shaders/cube.fs.c");

        uniformAngle = getUniformId("angle", program);
        attrib_vertex = glGetAttribLocation(program, "coordinate");
        attrib_vertex_color = glGetAttribLocation(program, "vertex_color");
    }

    void update() override {
        rotate_x += 0.1;
        rotate_y += 0.1;
        rotate_z += 0.1;
        render();
    }

    void render() const override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);

        glUseProgram(program);
        double pi = 3.1415926535897932;
        glUniform3f(uniformAngle,
                    (GLfloat)(rotate_x * pi / 180),
                    (GLfloat)(rotate_y * pi / 180),
                    (GLfloat)(rotate_z * pi / 180));

        glEnableVertexAttribArray(attrib_vertex);
        glEnableVertexAttribArray(attrib_vertex_color);

        glBindBuffer(GL_ARRAY_BUFFER, Vertex_VBO);
        glVertexAttribPointer(attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, Color_VBO);
        glVertexAttribPointer(attrib_vertex_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_QUADS, 0, 24);
        glDisableVertexAttribArray(attrib_vertex);
        glDisableVertexAttribArray(attrib_vertex_color);

        glUseProgram(0);
        checkOpenGLerror();
        glutSwapBuffers();
    }


    void initVBO()
    {
        vertex vertexes[] = {
                {-0.5, -0.5, -0.5},	{-0.5, 0.5, -0.5},	{-0.5, 0.5, 0.5},	{-0.5, -0.5, 0.5},
                {0.5, -0.5, -0.5},	{0.5, 0.5, -0.5},	{0.5, 0.5, 0.5},	{0.5, -0.5, 0.5},
                {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5},	{0.5, 0.5, -0.5},	{0.5, -0.5, -0.5},
                {-0.5, -0.5, 0.5},	{-0.5, 0.5, 0.5},	{0.5, 0.5, 0.5},	{0.5, -0.5, 0.5},
                {-0.5, -0.5, -0.5},	{0.5, -0.5, -0.5},	{0.5, -0.5, 0.5},	{-0.5, -0.5, 0.5},
                {-0.5, 0.5, -0.5},	{0.5, 0.5, -0.5},	{0.5, 0.5, 0.5},	{-0.5, 0.5, 0.5},
        };

        vertex colors[] = {
                {0.0, 1.0, 1.0},	{0.0, 0.0, 1.0},	{0.0, 1.0, 0.0},	{1.0, 1.0, 0.0},
                {1.0, 0.0, 1.0},	{1.0, 0.0, 0.0},	{1.0, 1.0, 1.0},	{0.0, 0.0, 0.0},
                {0.0, 1.0, 1.0},	{0.0, 0.0, 1.0},	{1.0, 0.0, 0.0},	{1.0, 0.0, 1.0},
                {1.0, 1.0, 0.0},	{0.0, 1.0, 0.0},	{1.0, 1.0, 1.0},	{0.0, 0.0, 0.0},
                {0.0, 1.0, 1.0},	{1.0, 0.0, 1.0},	{0.0, 0.0, 0.0},	{1.0, 1.0, 0.0},
                {0.0, 0.0, 1.0},	{1.0, 0.0, 0.0},	{1.0, 1.0, 1.0},	{0.0, 1.0, 0.0},
        };

        glGenBuffers(1, &Vertex_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Vertex_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

        glGenBuffers(1, &Color_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Color_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        checkOpenGLerror();
    }
};

#endif //OPENGLABS_TASK5_H
