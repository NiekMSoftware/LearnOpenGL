#include "pch.h"

static void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, 800, 600);
}

static void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// Toggle between wireframe and filled mode
	if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if(glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

// compilation
int success;
char infolog[512];

const char* vertexShaderSource{
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main() {\n"
" gl_Position = vec4(aPos, 1.0);\n"
" vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0"
};

const char* fragmentShaderSource{
"#version 460 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main() {"
" FragColor = ourColor;\n"
"}\0"
};

// triangle
float vertices[]{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW.\n";
		return -1;
	}

	// set up OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Shader Programming", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";

		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// setup viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// vert shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cerr << "ERROR::COMPILATION::SHADER::VERTEX::FAILED\n" << infolog << "\n";
	}

	// frag shader
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		std::cerr << "ERROR::COMPILATION::SHADER::FRAGMENT::FAILED\n" << infolog << "\n";
	}

	// shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cerr << "ERROR::LINKING::SHADER::PROGRAM::FAILED\n" << infolog << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	// print msg
	std::println("To switch between polygon modes press either:");
	std::println("Numpad 0: Wireframe Mode.");
	std::println("Numoad 1: Fill Mode.");

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// render and clear the color buffer
		glClearColor(0.4, 0.6, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// activate the shader
		glUseProgram(shaderProgram);

		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// now render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}