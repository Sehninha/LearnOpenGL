#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"

using namespace std;

// Callback function called everytime the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// OpenGL Viewport
	glViewport(0, 0, width, height); // X and Y of the lower left corner of the viewport, then Width and Height
	// Note: OpenGL renders from coordinates -1 to 1, then translates those coordinates to the viewport's dimension
}

// Input Function
void processInput(GLFWwindow* window)
{
	// Escape Key
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true); // Close the application window
	}
}

int main()
{
	// GLFW Window Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Major OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Minor OpenGL Version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window Object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); // Create window with Width, Height and Name
	if (window == NULL) // Error Handler
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Make the window context the main context on the current thread
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set window resize callback function

	// GLAD Initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Error Handler
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	Shader shader("vertexShader.vs", "fragmentShader.fs");

	// Triangle Vertices
	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO; // Vertex Array Object
					  // Stores vertex attribute configutarions and associated VBO's

	glGenVertexArrays(1, &VAO); // Generates a buffer ID to this object
	glBindVertexArray(VAO);		// Binds VAO first, then bind and set VBO's

	unsigned int VBO; // Vertex Buffer Object
					  // Stores vertex data on the GPU memory

	glGenBuffers(1, &VBO);				// Generates a buffer ID to this object
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds this object to the buffer type GL_ARRAY_BUFFER
										// Only one buffer of the same buffer type can be bind at once
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copies object data into the currently bound buffer
																			   // GL_STATIC_DRAW = Data will most likely not change
																			   // GL_DYNAMIC_DRAW = Data will likely change a lot
																			   // GL_STREAM_DRAW = Data will change every time it is drawn

		unsigned int EBO; // Element Buffer Object
					  // Stores vertex indices

	glGenBuffers(1, &EBO);						// Generates a buffer ID to this object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	// Binds this objects to the buffer type GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Tells OpenGL how to interpret the vertex data
	glVertexAttribPointer(0,							// Specifies the location of the vertex attribute -> layout (location = 0)
						  3,							// Size of the vertex attribute -> vec3
						  GL_FLOAT,						// Type of data -> float
						  GL_FALSE,						// Normlize data?
						  6 * sizeof(float),			// Stride (Space between consecutive vertex attributes)
						  (void*)0);					// Offset

	glEnableVertexAttribArray(0); // Enables vertex attribute at specified location

	// Tells OpenGL how to interpret the vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);						// Unbinds VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// Unbinds VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// Unbinds EBO

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draws objects in wireframe

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input process
		processInput(window);

		// Background Color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set background color
		glClear(GL_COLOR_BUFFER_BIT);		  // Clear color buffer with selected background color

		// Draw Stuff
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // Gets uniform variable location

		shader.use();
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); // Sets uniform variable value

		glBindVertexArray(VAO);				// Binds VAO

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// Drawing function (with EBO)
																// First Argument = Type of OpenGL drawing primitive
																// Second Argument = Number of indices total
																// Third Argument = Indices variable type
																// Fourth Argument = Offset

		//glDrawArrays(GL_TRIANGLES, 0, 3);	// Drawing function (without EBO)
		//									// First Argument = Type of OpenGL drawing primitive
		//									// Second Argument = Starting index of the vertex array
		//									// Third Argument = How many vertices should be drawn

		// Check and call events and swap buffers
		glfwPollEvents(); // Checks for inputs and events, updated the window state and call callback functions
		glfwSwapBuffers(window); // Output color buffer to the screen
	}

	glfwTerminate();
	return 0;
}