#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


#define GLEW_STATIC
#include <GLEW/glew.h>
#pragma comment(lib, "glew32s.lib")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Model {
public:
	std::vector<glm::vec3> verts;
	//std::vector<std::vector<GLuint>> faces;
	std::vector<GLuint> faces;
	std::vector<glm::vec3> norms;

	Model(const GLchar *filename);
	~Model();
	GLuint nverts();
	GLuint nfaces();
	glm::vec3 vert(GLuint i);
	GLuint face(GLuint idx);

	GLfloat* getVerts()
	{
		GLfloat *v = new GLfloat[nverts() * 3 * 2];

		for (int i = 0; i < nverts() * 3 * 2; i = i + 6)
		{
			v[i] = verts[i/6][0];
			v[i + 1] = verts[i/6][1];
			v[i + 2] = verts[i/6][2];
			v[i + 3] = norms[i/6][0];
			v[i + 4] = norms[i/6][1];
			v[i + 5] = norms[i/6][2];
		}

		return v;
	}


	GLuint* getInd()
	{

		GLuint *in = new GLuint[nfaces()];

		for (int i = 0; i < nfaces(); ++i)
			in[i] = faces[i];

		return in;
	}
};

