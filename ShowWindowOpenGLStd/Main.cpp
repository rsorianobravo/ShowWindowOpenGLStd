#include "libs.h"


Vertex verticesTriangle[] =
{
	// Position , Color, Texcoords

	glm::vec3(0.0f,0.5f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f), glm::vec3(1.f,0.f,0.f),
	glm::vec3(-0.5f,-0.5f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f),glm::vec3(0.f,1.f,0.f),
	glm::vec3(0.5f,-0.5f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f), glm::vec3(0.f,0.f,1.f)
};

Vertex vertices[] =
{
	// Position , Color, Texcoords

	
	glm::vec3(-0.5f,0.14f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f,0.f,-1.f),
	glm::vec3(-0.5f,-0.14f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec2(0.f,0.f), glm::vec3(0.f,0.f,-1.f),
	glm::vec3(0.5f,-0.14f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f),  glm::vec3(0.f,0.f,-1.f),
	
	glm::vec3(-0.5f,0.14f,0.f), glm::vec3(1.f,0.f,0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f,0.f,-1.f),
	glm::vec3(0.5f,-0.14f,0.f), glm::vec3(0.f,0.f,1.f), glm::vec2(1.f,0.f),  glm::vec3(0.f,0.f,-1.f),
	glm::vec3(0.5f,0.14f,0.f), glm::vec3(1.f,1.f,0.f), glm::vec2(1.f,1.f),   glm::vec3(0.f,0.f,-1.f)
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

/*********************************************************************************************/

// ------ method to calculate the frameBuffer
void framebuffer_resize_callback(GLFWwindow* wimdow, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

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

int main()
{

	// ------ Init GLFW lib
	glfwInit();

	// ------ Create Window
	const int WINDOW_WIDTH = 1080;
	const int WINDOW_HEIGHT = 1920;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// ------ macOS Compatibility
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "1", NULL, NULL);

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
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
	
	Shader core_program("vertex_core.glsl", "fragment_core.glsl", "");

	//GLuint core_program;
	//if (!loadShaders(core_program))
	//{
	//	glfwTerminate();
	//}


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

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);



	// Bind VAO 0
	glBindVertexArray(0);

	// Texture Init 

	// Texture 0
	/*
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
	*/

	Texture texture_0("images/Newtonlab Sin Sombra.png", GL_TEXTURE_2D, 0);


	// Texture 1
	/*
	int image_width1 = 0;
	int image_height1 = 0;
	unsigned char* image1 = SOIL_load_image("images/container.png", &image_width1, &image_height1, NULL, SOIL_LOAD_RGBA);

	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	if (image1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error Loading Texture" << "\n";
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image1);
	*/
	
	Texture texture_1("images/container.png", GL_TEXTURE_2D, 1);

	// Material 0

	Material material0(glm::vec3(0.1f), glm::vec3(1.f,1.f,1.f), glm::vec3(1.f), texture_0.getTextureUnit(), texture_1.getTextureUnit());


	// Init Matrices
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);
	
	// Transformations
	glm::mat4 ModelMatrix(1.f);

	/*
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, 0.f));

	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));
	*/

	ModelMatrix = glm::translate(ModelMatrix, position);

	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));

	ModelMatrix = glm::scale(ModelMatrix, scale);

	glm::vec3 camPosition(0.f,0.f, 2.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);

	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;

	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);


	// Lights
	glm::vec3 lightPos0(0.f, 0.f, 2.0f);



	// Init Uniforms

	//glUseProgram(core_program); 
	//core_program.use();
	
	core_program.setMat4fv(ModelMatrix, "ModelMatrix");
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	/*
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	*/

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");

	/*
	glUniform3fv(glGetUniformLocation(core_program, "lightPos0"), 1, glm::value_ptr(lightPos0));
	glUniform3fv(glGetUniformLocation(core_program, "cameraPos"), 1, glm::value_ptr(camPosition));
	*/

	//glUseProgram(0);

	// ------ Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// ------ Check update input 
		//glfwSetWindowShouldClose(window, true);
		glfwPollEvents();
		updateInput(window, position, rotation, scale);



		// ------ Update
		updateInput(window);
		// ------ Draw

		// ------ Clear
		glClearColor(0.1f, 0.1f, 0.1f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Use a Program
		//glUseProgram(core_program);
		core_program.use();


		// Update uniforms
		
		/*
		core_program.set1i(0, "texture0");
		core_program.set1i(1, "texture1");
		*/

		core_program.set1i(texture_0.getTextureUnit(), "texture0");
		core_program.set1i(texture_1.getTextureUnit(), "texture0");

		material0.sendToShader(core_program);

		/*
		glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);
		glUniform1i(glGetUniformLocation(core_program, "texture1"), 1);
		*/

		// Move Rotate Scale
		
		/*Rotation over the view
		
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, 0.f));

		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.09f), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));
		*/

		//rotation.y += 0.09f;
		//position.z += 0.001f;
		//scale.x += 0.001f;
		//scale.y += 0.001f;
		//scale.z += 0.001f;



		ModelMatrix = glm::mat4(1.f);

		ModelMatrix = glm::translate(ModelMatrix, position);

		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));

		ModelMatrix = glm::scale(ModelMatrix, scale);

		core_program.setMat4fv(ModelMatrix, "ModelMatrix");

		
		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));




		glfwGetFramebufferSize(window,&framebufferWidth, &framebufferHeight);
		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));


		// Use a Program
		core_program.use();


		// Activate Texture
		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		*/
		//texture_0.bind(0, GL_TEXTURE_2D);
		texture_0.bind();


		// Activate Texture 1
		/*
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		*/
		//texture_1.bind(1, GL_TEXTURE_2D);
		texture_1.bind();


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

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Delete Program
	//glDeleteProgram(core_program);

 	return 0;
}