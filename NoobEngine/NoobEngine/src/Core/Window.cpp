#include "nepch.h"
#include "Window.h"
#include "Events/Input.h"

#define GLFW_INCLUDE_NONE

namespace NoobEngine
{
	GLFWwindow* Window::m_Window = NULL;

	bool Window::CreateWindow(WindowProps _props)
	{
		// Init stuff
		if (!glfwInit()) {
			LOG_FATAL("Failed to initialize GLFW");
			TerminateWindow();
			return false;
		}
		LOG_INFO("GLFW initialized");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(_props.width, _props.height, _props.title, NULL, NULL);
		if (!m_Window) {
			LOG_FATAL("Failed to create GLFW window");
			TerminateWindow();
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		LOG_INFO("GLFWwindow created");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_FATAL("Failed to initialize GLAD");
			TerminateWindow();
			return false;
		}
		LOG_INFO("GLAD initialized");
		LOG_INFO("GL_VERSION %s", (const char*)glGetString(GL_VERSION));

		SetViewPort(800, 600);
		// Setup callbacks
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetKeyCallback(m_Window, Events::Input::Keyboard);
		glfwSetMouseButtonCallback(m_Window, Events::Input::Mouse);
		glfwSetCursorPosCallback(m_Window, Events::Input::Cursor);

		return true;
	}

	void Window::SetViewPort(uint32_t _width, uint32_t _height)
	{
		glViewport(0, 0, _width, _height);
	}

	int Window::WindowShouldClose() 
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::WindowShouldClose(bool _tf)
	{
		glfwSetWindowShouldClose(m_Window, _tf);
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

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
	{
		glfwMakeContextCurrent(_window);
		SetViewPort(_width, _height);
	}

}