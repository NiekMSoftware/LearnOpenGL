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
 
float vertices[]{
	// positions       // colors
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
	0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top
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

	// position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader shader{ 
		"shaders/triangle.vcb",
		"shaders/triangle.fcb" 
	};

	// print msg
	std::println("===================================================");
	std::println("To switch between polygon modes press either:");
	std::println("Numpad 0: Wireframe Mode.");
	std::println("Numpad 1: Fill Mode.");
	std::println("===================================================");

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// render and clear the color buffer
		glClearColor(0.4, 0.6, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// activate the shader
		shader.use();

		float timeValue = glfwGetTime();
		float offset = sin(timeValue) * 0.5f;
		shader.setFloat("offset", offset);

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