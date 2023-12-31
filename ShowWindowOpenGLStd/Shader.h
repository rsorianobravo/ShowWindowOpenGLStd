#pragma once

#include<iostream>
#include<fstream>
#include<string>


#include<glew/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include<glm/mat4x4.hpp>
#include<glm/gtc/type_ptr.hpp>

class Shader
{
private:
	
	// Attributes
	GLuint id;
	const int versionMajor;
	const int versionMinor;


	std::string loadShaderSource(const char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		// ------ Vertex
		//in_file.open("vertex_core.glsl");
		in_file.open(fileName);


		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "Error SHADER opening the shader file: " <<fileName << "\n";
			//loadSuccess = false;
		}

		in_file.close();

		std::string versionNr = std::to_string(this->versionMajor) + std::to_string(this->versionMinor)+"0";
		src.replace(src.find("#version"), 12, ("#version " + versionNr));
		std::cout << src << "\n";
		return src;
	}

	GLuint loadShader(GLenum type, const char* fileName)
	{
		
		//bool loadSuccess = true;

		char infoLog[512];
		GLint success;
		
		GLuint shader = glCreateShader(type);

		std::string str_src = this->loadShaderSource(fileName);

		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Error compiling the shader: " << fileName << "\n";
			std::cout << infoLog << "\n";
			//loadSuccess = false;
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader,  GLuint geometryShader, GLuint fragmentShader)
	{
		//bool loadSuccess = true;

		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

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
			//loadSuccess = false;
		}

		glUseProgram(0);

	}

public:

	// Constructors

	Shader(const int versionMajor, const int versionMinor, const char* vertexFile , const char* fragmentFile, const char* geometryFile = "")
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, "vertex_core.glsl");
		
		if(geometryFile != "")
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, "fragment_core.glsl");

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

	//Funtions
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void set1i(GLint value, const char* name)
	{
		this->use();
		glUniform1i(glGetUniformLocation(this->id, name), value);
		this->unuse();
	}
	
	
	void set1f(GLfloat value, const GLchar* name)
	{
		this->use();
		glUniform1f(glGetUniformLocation(this->id, name), value);
		this->unuse();
	}
	
	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		this->use();
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}
	
	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		this->use();
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		this->use();
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
		this->unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
		this->unuse();
	}

};
