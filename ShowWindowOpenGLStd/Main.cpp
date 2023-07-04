#include "libs.h"


Vertex verticesTriangle[] =
{
	// Position , Color, Texcoords

	glm::vec3(0.0f,0.5f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f),
	glm::vec3(-0.5f,-0.5f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f),
	glm::vec3(0.5f,-0.5f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f)
};

Vertex vertices[] =
{
	// Position , Color, Texcoords

	
	glm::vec3(-0.5f,0.5f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f),
	glm::vec3(-0.5f,-0.5f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f),
	glm::vec3(0.5f,-0.5f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f),
	
	glm::vec3(-0.5f,0.5f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f),
	glm::vec3(0.5f,-0.5f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f),
	glm::vec3(0.5f,0.5f,0.f), glm::vec3(1.f,1.f,0.f), glm::vec2(1.f,1.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

//GLuint indices[] = { 0, 1, 2, 3, 4, 5 };

GLuint indices[] = { 0, 1, 2, 0, 2, 5 };


unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

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
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1280;
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

	// ------ VAO VBO EBO
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;


	// ------ Gen VAO and Bind
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// ------ Gen VBO and Bind and send data
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ------ Gen EBO and Bind and send data
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	// Bind VAO 0
	glBindVertexArray(0);

	// Texture Init
	int image_width = 0;
	int image_height = 0;
	unsigned char* image = SOIL_load_image("images/pusheen.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error Loading Texture" << "\n";
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

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
		glClearColor(0.0f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Use a Program
		glUseProgram(core_program);

		// Update uniforms
		glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);

		// Activate Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		
		//Bind Vertex array object
		glBindVertexArray(VAO);
				
		// ------ Draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

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