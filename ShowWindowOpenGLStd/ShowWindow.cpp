#include "ShowWindow.h"

Quad quad = Quad();
Triangle triangle = Triangle();



//Private Functions
void ShowWindow::initGLFW()
{
	//Init GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT FAILED" << "\n";
		glfwTerminate();
	}
		
}

void ShowWindow::initWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);

	glfwWindowHint(GLFW_RESIZABLE, resizable);

	// ------ macOS Compatibility
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT FAILED" << "\n";
		glfwTerminate();
	}


	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(window, ShowWindow::framebuffer_resize_callback);
	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	// ------ Important
	glfwMakeContextCurrent(this->window);
}

void ShowWindow::initGLEW()
{
	// ------ Init Glew
	glewExperimental = GL_TRUE;

	// ------ Check the init status of Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::GLEW INIT" << "\n";
		glfwTerminate();
	}
	else
	{

	}
}

void ShowWindow::initOpenGLOptions()
{
	// ------ OpenGL Options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ShowWindow::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);

}

//Constructors

ShowWindow::ShowWindow(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable)
	:WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT), GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR)
{
	// Init Variables
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;
	
	// Init Matrices

	this->camPosition = glm::vec3(0.f, 0.f, 2.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initLights();
	this->initUniforms();

}

ShowWindow::~ShowWindow()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
	{
		delete this->shaders[i];
	}	for (size_t i = 0; i < this->textures.size(); i++)
	{
		delete this->textures[i];
	}
	for (size_t i = 0; i < this->materials.size(); i++)
	{
		delete this->materials[i]; 
	}
	for (size_t i = 0; i < this->meshers.size(); i++)
	{
		delete this->meshers[i];
	}
	for (size_t i = 0; i < this->lights.size(); i++)
	{
		delete this->lights[i];
	}
}



int ShowWindow::getWindowShouldClose()
{
	
	return glfwWindowShouldClose(this->window);
}

void ShowWindow::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void ShowWindow::update()
{
	// Update input
	// ------ Check update input 
	glfwPollEvents();
}

/******************************************************************/

// ------ Update

// ------ Draw

// ------ Clear

// Use a Program

// Update uniforms

// Move Rotate Scale

// Update Framebuffer size and projection matrix

// Use a Program

// Activate Texture

// ------ Draw

// ------ End Draw

/******************************************************************/


void ShowWindow::render()
{

	// ------ Update

	// ------ Draw

	// ------ Clear
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	// Use a Program

	// Update uniforms

	this->shaders[SHADER_CORE_PROGRAM]->set1i(this->textures[TEX_NEWTON0]->getTextureUnit(), "texture0");
	this->shaders[SHADER_CORE_PROGRAM]->set1i(this->textures[TEX_CONTAINER1]->getTextureUnit(), "texture1");

	this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	// Move Rotate Scale
	
	// Update Framebuffer size and projection matrix

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	// Use a Program
	this->shaders[SHADER_CORE_PROGRAM]->use();

	// Activate Texture

	this->textures[TEX_NEWTON0]->bind();
	// Activate Texture 1
	this->textures[TEX_CONTAINER1]->bind();

	// ------ Draw
	
	this->meshers[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

	// ------ End Draw
	glfwSwapBuffers(window);
	glFlush();

	// Reset 
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


// General Functions
// 
// ------ method to calculate the frameBuffer
void ShowWindow::framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}


void ShowWindow::initShaders()
{
	// ------ Shader Init

	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR, "vertex_core.glsl", "fragment_core.glsl", ""));
}

void ShowWindow::initTextures()
{
	// Texture Init 

	// Texture 0

	this->textures.push_back(new Texture("images/Newtonlab Sin Sombra.png", GL_TEXTURE_2D, 0));


	// Texture 1

	this->textures.push_back(new Texture("images/container.png", GL_TEXTURE_2D, 1));
}

void ShowWindow::initMaterials()
{
	// Material 0

	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f), this->textures[TEX_NEWTON0]->getTextureUnit(), this->textures[TEX_CONTAINER1]->getTextureUnit()));

}

void ShowWindow::initMeshes()
{
	// ------ Model Mesh

	//Mesh mesh(vertices, nrOfVertices,indices,nrOfIndices, glm::vec3(0.f),glm::vec3(0.f),glm::vec3(1.f));

	//Mesh mesh2(Quad().getVertices(), Quad().getNrOfVertices(), Quad().getIndices(), Quad().getNrOfIndices(), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

	//Mesh mesh(&quad, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

	//Mesh mesh1(&triangle, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

	this->meshers.push_back(new Mesh(&quad, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
}

void ShowWindow::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 2.0f));
}

void ShowWindow::initUniforms()
{
	// Init Uniforms


	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");


	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}



