#pragma once

#define GLEW_STATIC
#include <GLEW/glew.h>
#pragma comment(lib, "glew32s.lib")

#include <GLFW/glfw3.h>
#include <iostream>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>
#pragma comment(lib, "SOIL.lib")

#include "Shader.h"
#include "Camera.h"
#include "Model.h"


GLvoid key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
GLvoid mouse_callback(GLFWwindow* window, double xpos, double ypos);
GLvoid scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Game
{
private:
	GLFWwindow* window;
	GLint width, height;
	GLuint VBO, faceVBO;
	GLuint VAO, lightVAO, faceVAO;
	GLuint EBO, faceEBO;
	GLuint texture;
	Shader *shader, *shaderLight;



public:
	Game();
	~Game();

	GLvoid update();
	GLvoid do_movement();
};



