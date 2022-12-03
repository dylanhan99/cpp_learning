#pragma once
#include <stdint.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct GLFWwindow;

namespace NoobEngine 
{
	struct WindowProps {
		const char* title;
		uint32_t width, height;

		WindowProps(const char* title = "NoobEngine", uint32_t width = 800, uint32_t height = 600)
			: title(title), width(width), height(height) {}
	};

	class Window
	{
	private:
		static const char* title;
		static uint32_t width, height;

	public:
		static GLFWwindow* CreateWindow(WindowProps props);
		static void SetViewPort(uint32_t width, uint32_t height);

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void ProcessInput(GLFWwindow* window);
	};
}