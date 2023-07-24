#pragma once

#include "libs.h"


// Enummss

enum shader_enum 
{ 
	SHADER_CORE_PROGRAM = 0 
};
enum texture_enum 
{ 
	TEX_NEWTON = 0, TEX_NEWTONS = 1, TEX_CONTAINER = 2, TEX_CONTAINERS = 3
};
enum material_enum
{
	MAT_1 = 0
};
enum mesh_enum
{
	MESH_QUAD = 0,
	MESH_CONTAINER = 1
};

class ShowWindow
{
private:

	//Attributes
	//Window
	GLFWwindow* window;

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;

	float fov;
	float nearPlane;
	float farPlane;

	// Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Meshers
	std::vector<Mesh*> meshers;

	//Lights
	std::vector<glm::vec3*> lights;

	//Private Functions
	void initGLFW();

	void initWindow(const char* title, bool resizable);
	
	
	void initGLEW(); // --> Important after context Creation

	void initOpenGLOptions();

	void initMatrices();

	void initShaders();

	void initTextures();

	void initMaterials();

	void initMeshes();

	void initLights();

	void initUniforms();

	void updteUniforms();

	void updteUniformsCameraView();

	//Static variables

public:

// Constructors

	ShowWindow(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable);

	virtual ~ShowWindow();

	//Accesors
	int getWindowShouldClose();


	//Modifiers

	void setWindowShouldClose();


	//Functions
	void update();
	void render();

	//Static Functions
	static void framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh);
	static void updateInput(GLFWwindow* window);
	static void updateInput(GLFWwindow* window, Mesh& mesh);
	static void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
	void updateMouseInput();

	void updateInputCamera();


	

};

