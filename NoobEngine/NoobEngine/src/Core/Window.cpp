#include "nepch.h"
#include "Window.h"
#include "Events/Input.h"

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
		glfwSetKeyCallback(window, Events::Input::Keyboard);
		glfwSetMouseButtonCallback(window, Events::Input::Mouse);
		glfwSetCursorPosCallback(window, Events::Input::Cursor);

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

	void Window::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::ProcessInput(GLFWwindow* _window)
	{
		//if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		//	WindowShouldClose(_window, true);
		//}
		if (Events::Input::OnKeyPress(GLFW_KEY_W)) {
			LOG_TRACE("Pressed W");
		}
		if (Events::Input::OnKeyRepeat(GLFW_KEY_W)) {
			LOG_TRACE("Rep W");
		}
		if (Events::Input::OnKeyRelease(GLFW_KEY_W)) {
			LOG_TRACE("Released W");
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