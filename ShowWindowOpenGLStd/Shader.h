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

class Shader
{
private:

	GLuint id;

	std::string loadShaderSource(char* fileName)
	{
		return "";
	}

	GLuint loadShader(GLenum type, char* fileName)
	{

	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{

	} 

public:

	Shader(char* vertexFile, char* geometryFile, char* fragmentFile)
	{

	}

	~Shader()
	{
		glDeleteProgram(this->id);
	}

	// Set uniform functions
};