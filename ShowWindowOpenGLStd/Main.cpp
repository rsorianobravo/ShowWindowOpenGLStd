#include"ShowWindow.h"

/*
Primitive primitive = Primitive();
Quad quad = Quad();
Triangle triangle = Triangle();
*/

Vertex verticesTriangle[] =
{
	// Position , Color, Texcoords

	glm::vec3(0.0f,0.5f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f), glm::vec3(1.f,0.f,0.f),
	glm::vec3(-0.5f,-0.5f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f),glm::vec3(0.f,1.f,0.f),
	glm::vec3(0.5f,-0.5f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f), glm::vec3(0.f,0.f,1.f)
};

/*

Vertex vertices[] =
{
	// Position , Color, Texcoords, Normals

	
	glm::vec3(-0.5f,0.14f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f,0.f,1.f),
	glm::vec3(-0.5f,-0.14f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f), glm::vec3(0.f,0.f,1.f),
	glm::vec3(0.5f,-0.14f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f),  glm::vec3(0.f,0.f,1.f),
	
	glm::vec3(-0.5f,0.14f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f,0.f,1.f),
	glm::vec3(0.5f,-0.14f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f),  glm::vec3(0.f,0.f,1.f),
	glm::vec3(0.5f,0.14f,0.f), glm::vec3(1.f,1.f,0.f), glm::vec2(1.f,1.f),   glm::vec3(0.f,0.f,1.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

//GLuint indices[] = { 0, 1, 2, 3, 4, 5 };

GLuint indices[] = { 0, 1, 2, 0, 2, 5 };


unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

*/

/*********************************************************************************************/

/*
// ------ Talk about sending sizeof pointers and errors
void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
*/
/*********************************************************************************************/
/*
void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += 0.001f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotation.y -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotation.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		scale += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		scale -= 0.01f;
	}
}
*/
/*********************************************************************************************/
/*
void updateInput(GLFWwindow* window, Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.001f));
		//position.z -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, 0.001f));
		//position.z += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(-0.001f, 0.f, 0.f));
		//position.x -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.001f, 0.f, 0.f));
		//position.x += 0.001f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f,-0.01f,0.f));
		//rotation.y -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, +0.01f, 0.f));
		//rotation.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		mesh.scaleUpdate(glm::vec3(0.01f));
		//scale += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		mesh.scaleUpdate(glm::vec3(-0.01f));
		//scale -= 0.01f;
	}
}
*/
/*********************************************************************************************/

/* Copy to the ShowWindow Class
// ------ method to calculate the frameBuffer
void framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}
*/

/*********************************************************************************************/
/*
bool loadShaders(GLuint &program)
{
	bool loadSuccess = true;

	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	// ------ Vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "Error opening the vertex file" << "\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error compiling the vertex shader" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}


	temp = "";
	src = "";

	// ------ Fragment
	in_file.open("fragment_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "Error opening the fragment file" << "\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error compiling the fragment shader" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}



	// ------ Program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "Error linking the program" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	// ------ End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return loadSuccess;
}
*/
/*********************************************************************************************/

GLFWwindow* createWindow(const char* title, const int width, const int height, int& fbWidth, int& fbHeihgt, const int GLmajorVer, const int GLminorVer, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer);

	glfwWindowHint(GLFW_RESIZABLE, resizable);

	// ------ macOS Compatibility
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwGetFramebufferSize(window, &fbWidth, &fbHeihgt);
	glfwSetFramebufferSizeCallback(window, ShowWindow::framebuffer_resize_callback);
	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	// ------ Important
	glfwMakeContextCurrent(window);

	return window;
}


int main()
{

	ShowWindow showWindow("ShowWindowOpenGL", 1080, 1920, 4, 5, true);

	// ------ Shader Init
	
	// ------ Model Mesh

	// Texture Init 

	// Init Matrices
	
	// Lights
	
	// Init Uniforms

	

	// ------ Main Loop
	while (!showWindow.getWindowShouldClose())
	{
		// ------ Check update input 
		showWindow.update();
		showWindow.render();
	}


	// ------ End Program


	// Delete Program
	//glDeleteProgram(core_program);

	// Delete VAO and Buffers



 	return 0;
}