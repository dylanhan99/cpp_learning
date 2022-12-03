#include "../inc/Window.h"

#include <glad.h>
#include <glfw3.h>
#include <iostream>

namespace NoobEngine
{
	GLFWwindow* Window::CreateWindow(WindowProps props)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "NoobEngine", NULL, NULL);
		if (!window) {
			std::cout << "Failed to create GLFW window!\n";
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return nullptr;
		}

		SetViewPort(800, 600);
		// Setup callbacks
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		return window;
	}

	void Window::SetViewPort(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glfwMakeContextCurrent(window);
		SetViewPort(width, height);
	}

	void Window::ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

}