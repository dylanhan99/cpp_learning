#pragma once

#include "nepch.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct GLFWwindow;

namespace NoobEngine 
{
	struct WindowProps {
		const char* title;
		uint32_t width, height;

		WindowProps(const char* title = "NoobEngine", 
			uint32_t width = 800, uint32_t height = 600)
			: title(title), width(width), height(height) {}
	};

	class Window
	{
	private:
		static const char* title;
		static uint32_t width, height;

	public:
		Window();
		~Window();

		static GLFWwindow* CreateWindow(WindowProps _props);
		static void SetViewPort(uint32_t _width, uint32_t _height);
		static int  WindowShouldClose(GLFWwindow* _window);
		static void WindowShouldClose(GLFWwindow* _window, bool _tf);
		static void TerminateWindow();

		static void Clear();
		static void ProcessInput(GLFWwindow* _window);
		static void SwapBuffers(GLFWwindow* _window);

		static void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height);
	};
}