//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
//! ���������� � ����������������� ID
//! ID ��������� ���������
GLuint Program;
//! ID ��������
GLint Attrib_vertex;
//! ID ������� ���������� �����
GLint Unif_color;
//! ID Vertex Buffer Object
GLuint VBO;
//! �������
struct vertex
{
	GLfloat x;
	GLfloat y;
};

//! ������� ������ ���� �������
void shaderLog(unsigned int shader)
{
	int infologLen = 0;
	int charsWritten = 0;
	char* infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
	if (infologLen > 1)
	{
		infoLog = new char[infologLen];
		if (infoLog == NULL)
		{
			std::cout << "ERROR: Could not allocate InfoLog buffer\n";
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout << "InfoLog: " << infoLog << "\n\n\n";
		delete[] infoLog;
	}
}
//! �������� ������ OpenGL, ���� ���� �� ����� � ������� ��� ������
void checkOpenGLerror()
{
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error! - " << gluErrorString(errCode);
}
//! ������������� �������� ��� ���������� ��������
void initShaderforStripedSquare()
{
	//! �������� ��� ��������
	const char* vsSource =
		"attribute vec2 coord;\n"
		"void main() {\n"
		" gl_Position = vec4(coord, 0.0, 1.0);\n"
		"}\n";
	const char* fsSource =
		"uniform vec4 color;\n"
		"void main() {\n"
		" if (mod(gl_FragCoord.x, 10)<5.0) \n"
		" gl_FragColor = color;\n"
		" else\n"
		" gl_FragColor = vec4(1.0,0.0,1.0,0.0);\n"
		"}\n";
	//! ���������� ��� �������� ��������������� ��������
	GLuint vShader, fShader;
	//! ������� ��������� ������
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//! �������� �������� ���
	glShaderSource(vShader, 1, &vsSource, NULL);
	//! ����������� ������
	glCompileShader(vShader);
	std::cout << "vertex shader \n";
	shaderLog(vShader);
	//! ������� ����������� ������
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//! �������� �������� ���
	glShaderSource(fShader, 1, &fsSource, NULL);
	//! ����������� ������
	glCompileShader(fShader);
	std::cout << "fragment shader \n";
	shaderLog(fShader);
	//! ������� ��������� � ����������� ������� � ���
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);
	//! ������� ��������� ���������
	glLinkProgram(Program);
	//! ��������� ������ ������
	int link_ok;
	glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
	if (!link_ok)
	{
		std::cout << "error attach shaders \n";
		return;
	}
	///! ���������� ID �������� �� ��������� ���������
	const char* attr_name = "coord";
	Attrib_vertex = glGetAttribLocation(Program, attr_name);
	if (Attrib_vertex == -1)
	{
		std::cout << "could not bind attrib " << attr_name << std::endl;
		return;
	}
	//! ���������� ID �������
	const char* unif_name = "color";
	Unif_color = glGetUniformLocation(Program, unif_name);
	if (Unif_color == -1)
	{
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}
	checkOpenGLerror();
}

//! ������������� �������� ��� ���������� ��������
void initShaderforChessboardSquare()
{
	//! �������� ��� ��������
	const char* vsSource =
		"attribute vec2 coord;\n"
		"void main() {\n"
		" gl_Position = vec4(coord, 0.0, 1.0);\n"
		"}\n";
	const char* fsSource =
		"uniform vec4 color;\n"
		"void main() {\n"
		" if (mod(gl_FragCoord.x, 10)<5.0 ^^ mod(gl_FragCoord.y, 10)<5.0) \n"
		" gl_FragColor = color;\n"
		" else\n"
		" gl_FragColor = vec4(1.0,0.0,1.0,0.0);\n"
		"}\n";
	//! ���������� ��� �������� ��������������� ��������
	GLuint vShader, fShader;
	//! ������� ��������� ������
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//! �������� �������� ���
	glShaderSource(vShader, 1, &vsSource, NULL);
	//! ����������� ������
	glCompileShader(vShader);
	std::cout << "vertex shader \n";
	shaderLog(vShader);
	//! ������� ����������� ������
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//! �������� �������� ���
	glShaderSource(fShader, 1, &fsSource, NULL);
	//! ����������� ������
	glCompileShader(fShader);
	std::cout << "fragment shader \n";
	shaderLog(fShader);
	//! ������� ��������� � ����������� ������� � ���
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);
	//! ������� ��������� ���������
	glLinkProgram(Program);
	//! ��������� ������ ������
	int link_ok;
	glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
	if (!link_ok)
	{
		std::cout << "error attach shaders \n";
		return;
	}
	///! ���������� ID �������� �� ��������� ���������
	const char* attr_name = "coord";
	Attrib_vertex = glGetAttribLocation(Program, attr_name);
	if (Attrib_vertex == -1)
	{
		std::cout << "could not bind attrib " << attr_name << std::endl;
		return;
	}
	//! ���������� ID �������
	const char* unif_name = "color";
	Unif_color = glGetUniformLocation(Program, unif_name);
	if (Unif_color == -1)
	{
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}
	checkOpenGLerror();
}
//! ������������� VBO
void initVBOforSquare()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//! ������� ������ ������������
	vertex square[4] = {
	{ -0.5f, -0.5f },
	{ -0.5f, 0.5f },
	{ 0.5f, 0.5f },
	{ 0.5f, -0.5f },
	};
	//! �������� ������� � �����
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
	checkOpenGLerror();
}
//! ������������ ��������
void freeShader()
{
	//! ��������� ����, �� ��������� �������� ���������
	glUseProgram(0);
	//! ������� ��������� ���������
	glDeleteProgram(Program);
}
//! ������������ ������
void freeVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);
}
void resizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}
//! ���������
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//! ������������� ��������� ��������� �������
	glUseProgram(Program);
	static float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//! �������� ������� � ������
	glUniform4fv(Unif_color, 1, red);
	//! �������� ������ ���������
	glEnableVertexAttribArray(Attrib_vertex);
	//! ���������� VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//! �������� pointer 0 ��� ������������ ������, �� ��������� ��� ������ � VBO
	glVertexAttribPointer(Attrib_vertex, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//! ��������� VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//! �������� ������ �� ����������(������)
	glDrawArrays(GL_QUADS, 0, 4);
	//! ��������� ������ ���������
	glDisableVertexAttribArray(Attrib_vertex);
	//! ��������� ��������� ���������
	glUseProgram(0);
	checkOpenGLerror();
	glutSwapBuffers();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Simple shaders");
	glClearColor(0, 0, 0, 0);
	//! ����������� ����� �������������� ��������
	GLenum glew_status = glewInit();
	if (GLEW_OK != glew_status)
	{
		//! GLEW �� ���������������������
		std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
		return 1;
	}
	//! ��������� ����������� OpenGL 2.0
	if (!GLEW_VERSION_2_0)
	{
		//! OpenGl 2.0 ��������� �� ��������
		std::cout << "No support for OpenGL 2.0 found\n";
		return 1;
	}
	//! �������������
	initVBOforSquare();
	//initShaderforStripedSquare();
	initShaderforChessboardSquare();
	glutReshapeFunc(resizeWindow);
	glutDisplayFunc(render);
	glutMainLoop();
	//! ������������ ��������
	freeShader();
	freeVBO();
}