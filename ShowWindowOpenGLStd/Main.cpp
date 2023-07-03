#include "libs.h"


/*********************************************************************************************/

// method to calculate the frameBuffer
void framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

/*********************************************************************************************/

bool loadShaders(GLuint &program)
{
	char infoLog[512];
	GLuint success;
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

	// ------ Shader Init
	GLuint core_program;
	loadShaders(core_program);


	// ------ Model

	// ------ VAO VBO





	// ------ Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// ------ Check update input
		//glfwSetWindowShouldClose(window, true);
		glfwPollEvents();

		// ------ Update

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
	glfwTerminate();

 	return 0;
}