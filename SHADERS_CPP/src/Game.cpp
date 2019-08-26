
#include "include/Game.h"

GLboolean keys[1024];
Camera cam;
GLuint WIDTH = 800;
GLuint HEIGHT = 600;
GLfloat fov = 45.0f;

GLvoid key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	cam.update(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}



GLfloat vertices[] = {
	// Позиции              //Нормали
	 0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 0.5f,
	 0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 0.5f,
	-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 0.5f,
	-0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 0.5f,

	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, -0.5f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -0.5f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -0.5f,
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, -0.5f,

	 0.5f,  0.5f, -0.5f,	0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.5f,		0.5f, 0.0f, 0.0f,
	 0.5f,  0.5f, 0.5f,		0.5f, 0.0f, 0.0f,

	-0.5f,  0.5f, 0.5f,		-0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,		-0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	-0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	-0.5f, 0.0f, 0.0f,

	 0.5f,  0.5f, 0.5f,		0.0f, 0.5f, 0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 0.5f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 0.5f, 0.0f,
	-0.5f,  0.5f, 0.5f,		0.0f, 0.5f, 0.0f,

	 0.5f, -0.5f, 0.5f,		0.0f, -0.5f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, -0.5f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.5f,		0.0f, -0.5f, 0.0f,
};

GLuint indices[] = {  // Помните, что мы начинаем с 0!
	0, 1, 3,   // Первый треугольник
	1, 2, 3,  // Второй треугольник

	4, 5, 7,   // Первый треугольник
	5, 6, 7,  // Второй треугольник

	8, 9, 11,   // Первый треугольник
	9, 10, 11,  // Второй треугольник

	12, 13, 15,   // Первый треугольник
	13, 14, 15,  // Второй треугольник

	16, 17, 19,   // Первый треугольник
	17, 18, 19,  // Второй треугольник

	20, 21, 23,   // Первый треугольник
	21, 22, 23,  // Второй треугольник

	24, 25, 27,   // Первый треугольник
	25, 26, 27,  // Второй треугольник

	28, 29, 31,   // Первый треугольник
	29, 30, 31,  // Второй треугольник
};

glm::vec3 cubePositions[] = {
  glm::vec3(5.0f,  5.0f,  5.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 lightPos(-4.0f, -4.0f, 20.0f);



Model man = Model("model/head.obj");
GLfloat *verts = man.getVerts();
GLuint *inds = man.getInd();

Game::Game()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "OPENGL TEST", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	
	shader = new Shader("shaders/vert.txt", "shaders/fragm.txt");
	shaderLight = new Shader("shaders/vert_light.txt", "shaders/fragm_light.txt");
	//_______________________________
	   
	//int width, height;
	//unsigned char* image = SOIL_load_image("img/box.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	
	/*glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);*/


	//_______________________________
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	   
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint step = 6;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//_________________________________
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	//_________________________________


	

	glGenVertexArrays(1, &faceVAO);
	glGenBuffers(1, &faceVBO);
	glGenBuffers(1, &faceEBO);

	glBindVertexArray(faceVAO);

	glBindBuffer(GL_ARRAY_BUFFER, faceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * man.nverts() * 3 * 2, verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * man.nfaces(), inds, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	for (int i = 0; i < 1000; i++)
		std::cout << inds[i] << " ";
}



Game::~Game()
{
	delete shader;
	delete shaderLight;

	delete verts;
	delete inds;
	glfwTerminate();
};



GLvoid Game::do_movement()
{	
	cam.move(keys[GLFW_KEY_W], keys[GLFW_KEY_S], keys[GLFW_KEY_A], keys[GLFW_KEY_D]);
}




GLvoid Game::update()
{

	   

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		do_movement();

		glClearColor(0.f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = cam.getLookAt();
		glm::mat4 projection = glm::perspective(glm::radians(fov), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);


		shader->Use();

		GLint viewLoc = glGetUniformLocation(shader->Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		GLint projLoc = glGetUniformLocation(shader->Program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		shader->setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
		shader->setVec3("viewPos", cam.cameraPos.x, cam.cameraPos.y, cam.cameraPos.z);

		shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader->setFloat("material.shininess", 32.0f);

		//glBindTexture(GL_TEXTURE_2D, texture);		
		
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 new_model = glm::translate(model, cubePositions[i]);
			new_model = glm::rotate(new_model, glm::radians(i*15.0f), glm::vec3(1.0f, 1.0f, 0.0f));
			GLint new_modelLoc = glGetUniformLocation(shader->Program, "model");
			glUniformMatrix4fv(new_modelLoc, 1, GL_FALSE, glm::value_ptr(new_model));

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(faceVAO);

		glm::mat4 new_model = glm::translate(model, glm::vec3(-10.0f, -10.0f, -10.0f));
		new_model = glm::scale(model, glm::vec3(5.0f));
		GLint new_modelLoc = glGetUniformLocation(shader->Program, "model");
		glUniformMatrix4fv(new_modelLoc, 1, GL_FALSE, glm::value_ptr(new_model));
		glDrawElements(GL_TRIANGLES, man.nfaces(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		shaderLight->Use();

		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));

		GLint modelLocLight = glGetUniformLocation(shaderLight->Program, "model");
		glUniformMatrix4fv(modelLocLight, 1, GL_FALSE, glm::value_ptr(model));
		GLint viewLocLight = glGetUniformLocation(shaderLight->Program, "view");
		glUniformMatrix4fv(viewLocLight, 1, GL_FALSE, glm::value_ptr(view));
		GLint projLocLight = glGetUniformLocation(shaderLight->Program, "projection");
		glUniformMatrix4fv(projLocLight, 1, GL_FALSE, glm::value_ptr(projection));		
			

		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		glfwSwapBuffers(glfwGetCurrentContext());
		//glfwSwapBuffers(window);
	}
}


