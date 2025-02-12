#include "pch.h"

static void frameBufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window) {
	static bool wireframe = false;
	static bool zeroKeyPressed = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// Toggle wireframe mode when W is pressed
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		if (!zeroKeyPressed) {  // Only toggle once per key press
			wireframe = !wireframe;
			glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
			zeroKeyPressed = true;
		}
	}
	else {
		zeroKeyPressed = false;
	}
}

const char* vertexShaderSource =
"#version 440 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 440 core\n"
"out vec4 FragColor;"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* yellowFragmentShaderSource =
"#version 440 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n"
"}\0";

int main()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW.";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD.\n";
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	// TODO: Exercise 1; Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.
	float triangleVertices[] = {
		// first triangle
		-0.3f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,
		-0.2f, 0.1f, 0.0f,

		// second triangle
		0.3f, -0.1f, 0.0f,
		0.1f, -0.1f, 0.0f,
		0.2f, 0.1f, 0.0f
	};

	// TODO: Exercise 2; Now create the same 2 triangles using two different VAOs and VBOs for their data.
	float triangle1Vertices[] = {
		-0.3f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,
		-0.2f, 0.1f, 0.0f
	};
	float triangle2Vertices[] = {
		0.3f, -0.1f, 0.0f,
		0.1f, -0.1f, 0.0f, 
		0.2f, 0.1f, 0.0f
	};


	// define the rectangle
	float rectVertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	unsigned int triangle1VAO, triangle1VBO;
	glGenVertexArrays(1, &triangle1VAO);
	glBindVertexArray(triangle1VAO);
	glGenBuffers(1, &triangle1VBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangle1VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1Vertices), triangle1Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int triangle2VAO, triangle2VBO;
	glGenVertexArrays(1, &triangle2VAO);
	glBindVertexArray(triangle2VAO);
	glGenBuffers(1, &triangle2VBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangle2VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2Vertices), triangle2Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// vertex array object
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// element buffer object
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// compile vertex shader
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	// fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Compile
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	// yellow frag shader
	unsigned int yellowFragmentShader;
	yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
	glCompileShader(yellowFragmentShader);
	glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::YELLOW::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	// shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	// TODO: Create two shader programs where the second program uses a different fragment shader
	// that outputs the color yellow; draw both triangles again where one outputs the color yellow.
	unsigned int yellowShaderProgram;
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowFragmentShader);
	glLinkProgram(yellowShaderProgram);
	glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::YELLOW::PROGRAM::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(yellowFragmentShader);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(triangle1VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(yellowShaderProgram);
		glBindVertexArray(triangle2VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // rectangle

		// check all events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}