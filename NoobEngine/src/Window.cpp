#include "Window.h"

#include <glad.h>
#include <glfw3.h>
#include <iostream>

namespace NoobEngine
{
	Window::Window()
	{

	}

	Window::~Window() 
	{
		TerminateWindow();
	}

	GLFWwindow* Window::CreateWindow(WindowProps _props)
	{
		// Init stuff
		if (!glfwInit()) {
			std::cout << "GLFW init fail\n";
			TerminateWindow();
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(_props.width, _props.height, _props.title, NULL, NULL);
		if (!window) {
			std::cout << "Failed to create GLFW window!\n";
			TerminateWindow();
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

	void Window::SetViewPort(uint32_t _width, uint32_t _height)
	{
		glViewport(0, 0, _width, _height);
	}

	int Window::WindowShouldClose(GLFWwindow* _window) 
	{
		return glfwWindowShouldClose(_window);
	}

	void Window::WindowShouldClose(GLFWwindow* _window, bool _tf)
	{
		glfwSetWindowShouldClose(_window, _tf);
	}

	void Window::TerminateWindow()
	{
		glfwTerminate();
	}

	void Window::ProcessInput(GLFWwindow* _window)
	{
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			WindowShouldClose(_window, true);
		}
	}

	void Window::SwapBuffers(GLFWwindow* _window)
	{
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	void Window::framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
	{
		glfwMakeContextCurrent(_window);
		SetViewPort(_width, _height);
	}

}