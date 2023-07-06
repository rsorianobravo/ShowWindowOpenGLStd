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
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		// ------ Vertex
		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "Error opening the vertex file" << fileName << "\n";
		}

		in_file.close();

		return src; 
	}

	GLuint loadShader(GLenum type, char* fileName)
	{
		bool loadSuccess = true;

		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(GL_VERTEX_SHADER);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();

		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Error SHADER compiling the vertex shader" << fileName << "\n";
			std::cout << infoLog << "\n";
			loadSuccess = false;
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		bool loadSuccess = true;

		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();
		//glUseProgram(this->id)

		glAttachShader(this->id, vertexShader);
		 
		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}

		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "Error SHADER linking the program" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);

	} 

public:

	Shader(char* vertexFile, char* geometryFile, char* fragmentFile)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;
		 
		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

		if(geometryFile != "")
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		// ------ End
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);


	}

	~Shader()
	{
		glDeleteProgram(this->id);
	}

	// Set uniform functions
};