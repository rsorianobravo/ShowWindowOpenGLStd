#pragma once

#include<iostream>
#include<vector>

#include"Material.h"
#include"Shader.h"
#include"Vertex.h"
#include"Texture.h"



class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector <GLuint> indices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void initVertexData(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertexArray[i]);
		}		
		
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indexArray[i]);
		}
	}

	void initVAO()
	{
		// ------ VAO VBO EBO
		//GLuint VAO;
		//GLuint VBO;
		//GLuint EBO;


		// ------ Gen VAO and Bind
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// ------ Gen VBO and Bind and send data
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		// ------ Gen EBO and Bind and send data
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


		// ------ Set Vertex Attribute Pointers and Enable

		/* If the location is not defined in the vertex core file....
		GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(attribLoc);
		*/


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);



		// Bind VAO 0
		glBindVertexArray(0);
	}

	void initModelMatrix()
	{
		
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);

		// Transformations
		this->ModelMatrix = glm::mat4(1.f);

		/*
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, 0.f));

		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));
		*/

		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);

		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));

		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}

	void updateUniforms(Shader* shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

public:
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
	{
		this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->initVAO();
		this->initModelMatrix();
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	void update()
	{

	}

	void render(Shader* shader) 
	{
		// Update Uniforms
		this->updateUniforms(shader);

		//Bind Vertex array object
		glBindVertexArray(this->VAO);

		// Render
		// ------ Draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);






	}

};
