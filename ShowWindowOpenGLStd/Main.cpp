#include "libs.h"


Vertex vertices[] =
{
	// Position
	glm::vec3(0.0f,0.5f,0.f), glm::vec3(1.f,0.f,0.f),
	glm::vec3(-0.5f,-0.5f,0.f), glm::vec3(0.f,1.f,0.f),
	glm::vec3(0.5f,-0.5f,0.f), glm::vec3(0.f,0.f,1.f),
};

/*********************************************************************************************/

// ------ Talk about sending sizeof pointers and errors
void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

/*********************************************************************************************/

// ------ method to calculate the frameBuffer
void framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

/*********************************************************************************************/

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
/*********************************************************************************************/

int main()
{

	// ------ Init GLFW lib
	glfwInit();

	// ------ Create Window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// ------ macOS Compatibility
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "1", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	// ------ Important
	glfwMakeContextCurrent(window);

	// ------ Init Glew
	glewExperimental = GL_TRUE;

	// ------ Check the init status of Glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR" << "\n";
		glfwTerminate();
	}
	else
	{

	}

	// ------ OpenGL Options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// ------ Shader Init
	GLuint core_program;
	if (!loadShaders(core_program))
	{
		glfwTerminate();
	}


	// ------ Model

	// ------ VAO VBO





	// ------ Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// ------ Check update input
		//glfwSetWindowShouldClose(window, true);
		glfwPollEvents();

		// ------ Update
		updateInput(window);
		// ------ Draw

		// ------ Clear
		glClearColor(0.345f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// ------ Draw

		// ------ End Draw
		glfwSwapBuffers(window);
		glFlush();
	}


	// ------ End Program
	glfwDestroyWindow(window);
	glfwTerminate();

	// Delete Program
	glDeleteProgram(core_program);

 	return 0;
}