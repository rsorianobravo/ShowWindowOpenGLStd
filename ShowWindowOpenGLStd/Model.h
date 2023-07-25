#pragma once

#include"Mesh.h"
#include"Texture.h"
#include"Shader.h"
#include"Material.h"

class Model
{
private:

	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;

	std::vector<Mesh*> meshes;

	glm::vec3 position;

	void  updteUniforms()
	{

	}


public:
	
	/*********************************************************************************************/
	
	Model(glm::vec3 position, Material* material, Texture* overrideTextureDiff, Texture* overrideTextureSpec, std::vector<Mesh*> meshes)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overrideTextureDiff;
		this->overrideTextureSpecular = overrideTextureSpec;

		for (auto*i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

	}

	/*********************************************************************************************/

	~Model()
	{
		for (auto*& i : this->meshes)
		{
			delete i;
		}
	}

	//Functions

	/*********************************************************************************************/

	void update()
	{

	}

	/*********************************************************************************************/

	void render(Shader* shader)
	{
		// Update uniforms
		this->updteUniforms();
		//this->updteUniformsCameraView();
		//this->updteUniformsCameraViewMouse();

		// Update uniforms
		 

		this->material->sendToShader(*shader);

		// Use a Program
		shader->use();

		
		// Activate Texture 1 Mesh 1

		overrideTextureDiffuse->bind(0);
		overrideTextureSpecular->bind(1);

		// ------ Draw
		for (auto& i : this->meshes)
		{
			i->render(shader);
		}


	}

};