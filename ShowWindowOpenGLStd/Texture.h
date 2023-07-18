#include<iostream>
#include<string>


#include<glew/glew.h>
#include<GLFW/glfw3.h>


#include<SOIL2/SOIL2.h>

class Texture
{
private:
	GLuint id;
	int height;
	int width;

public:

	Texture(const char* fileName, GLenum type)
	{
		// Texture 0

		//int image_width = 0;
		//int image_height = 0;

		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		//GLuint texture0;
		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		if (image)
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		else
		{
			std::cout << "Error Loading Texture" << "\n";
		}

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
	}

	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	GLuint getID() const
	{
		return this->id;
	}

	void bind(GLint texture_uint, GLenum type)
	{
		glActiveTexture(GL_TEXTURE0 + texture_uint);
		glBindTexture(type, this->id);
	}

	void unbind(GLenum type)
	{
		glActiveTexture(0);
		glBindTexture(type, 0);
	}
};