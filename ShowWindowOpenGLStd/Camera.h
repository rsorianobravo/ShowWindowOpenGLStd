#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>


#include<glew/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

enum direction {FORWARD = 0, BACKWARD = 1, LEFT = 2, RIGHT = 3};

class Camera
{
private:
	glm::mat4 ViewMatrix;
	
	GLfloat movementSpeed;
	GLfloat sensivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	void updateCameraVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));

	}

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
	{
		this->ViewMatrix = glm::mat4(1.f);

		this->movementSpeed = 0.3f;
		this->sensivity = 0.05f;

		this->worldUp = worldUp;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = worldUp;

		this->pitch = 0.f;
		this->yaw = -90.f;
		this->roll = 0.f;

		this->updateCameraVectors();
	}
	~Camera() 
	{

	}

	//Accesors
	const glm::mat4 getViewMatrix()
	{
		this->updateCameraVectors();
		this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

		return this->ViewMatrix;
	}

	const glm::vec3 getPosition() const
	{
		return this->position;
	}

	//Functions

	void updateKeyboardInput(const float& dt, const int direction)
	{
		//Update Position vector
		switch (direction)
		{
		case FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
		default:
			break;
		}
	}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
	{
		// Update Pitch, yaw and roll
		this->pitch += static_cast<GLfloat>(offsetY) * this->sensivity * dt;

		this->yaw += static_cast<GLfloat>(offsetX) * this->sensivity * dt;

		if (this->pitch > 80.f)
			this->pitch = 80.f;
		else if (this->pitch < -80.f)
			this->pitch = -80.f;

		if (this->yaw > 360.f || this->yaw < -360.f)
			this->yaw = 0.f;


	}


	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
	{
		this->updateKeyboardInput(dt, direction);
		this->updateMouseInput(dt, offsetX, offsetY);
	}
};