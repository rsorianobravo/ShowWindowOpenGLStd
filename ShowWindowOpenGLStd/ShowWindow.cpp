#include "ShowWindow.h"




//Private Functions
void ShowWindow::initGLFW()
{
	//Init GLFW
	glfwInit();
}

void ShowWindow::initWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);

	glfwWindowHint(GLFW_RESIZABLE, resizable);

	// ------ macOS Compatibility
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	glfwGetFramebufferSize(window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(window, ShowWindow::framebuffer_resize_callback);
	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	// ------ Important
	glfwMakeContextCurrent(window);
}

//Constructors

ShowWindow::ShowWindow(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable)
	:WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT), GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR)
{
	// Init Variables
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;
	
	this->initWindow(title, resizable);
}

ShowWindow::~ShowWindow()
{

}

// General Functions
// 
// ------ method to calculate the frameBuffer
void ShowWindow::framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

