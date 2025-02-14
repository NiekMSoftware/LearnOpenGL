#include "pch.h"

static void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initailize GLFW.";
		return -1;
	}

	// setup version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, Window!", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create a GLFW window.\n";
		
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD.\n";
		
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// viewport with resizable window
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// render a nice blue color
		glClearColor(0.2, 0.3, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// poll events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}