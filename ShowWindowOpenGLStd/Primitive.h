#pragma once

#include<glew/glew.h>
#include<GLFW/glfw3.h>
#include<vector>
#include"Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector <GLuint> indices;

public:
	Primitive()
	{

	}

	virtual ~Primitive()
	{

	}
	 
	// Functions

	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices()
	{
		return this->vertices.data();
	}

	inline GLuint* getIndices()
	{
		return this->indices.data();
	}

	inline const unsigned getNrOfVertices()
	{
		return this->vertices.size();
	}

	inline const unsigned getNrOfIndices()
	{
		return this->indices.size();
	}

};
