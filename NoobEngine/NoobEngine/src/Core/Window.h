#pragma once

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
		//static const char* title;
		//static uint32_t width, height;
		static GLFWwindow* m_Window;
		static float m_Width;
		static float m_Height;

	public:
		static bool CreateWindow(WindowProps _props);
		static void SetViewPort(uint32_t _width, uint32_t _height);
		static int  WindowShouldClose();
		static void WindowShouldClose(bool _tf);
		static void TerminateWindow();

		static void Clear();
		static void SwapBuffers();

		static inline const float GetWidth() { return m_Width; }
		static inline const float GetHeight() { return m_Height; }

		static void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height);
	};
}