#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
private:
	GLfloat lastX = 0, lastY = 0;
	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;
	GLboolean firstMouse = true;

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	GLfloat cameraSpeed = 0.05f;


public:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	glm::mat4 getLookAt() {
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	GLvoid move(GLboolean forward, GLboolean backward, GLboolean left, GLboolean right) {
		if (forward)
			cameraPos += cameraSpeed * cameraFront;
		if (backward)
			cameraPos -= cameraSpeed * cameraFront;
		if (left)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (right)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	void update(double xpos, double ypos) {
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		GLfloat sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}


};


