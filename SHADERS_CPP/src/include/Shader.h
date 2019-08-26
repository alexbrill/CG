#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GLEW/glew.h>
#pragma comment(lib, "glew32s.lib")

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();
	void setVec3(const GLchar*, GLfloat, GLfloat, GLfloat);
	void setFloat(const GLchar*, GLfloat);
};

#endif