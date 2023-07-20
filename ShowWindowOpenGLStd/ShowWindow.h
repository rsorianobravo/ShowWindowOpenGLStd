#pragma once

#include "libs.h"




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


	//Private Functions
	void initGLFW();

	void initWindow(const char* title, bool resizable);
	
	
	void initGLEW(); // --> Important after context Creation

	void initOpenGLOptions();


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

};

