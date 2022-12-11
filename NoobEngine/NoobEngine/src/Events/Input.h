#pragma once

namespace NoobEngine { namespace Events {

	class Input
	{
	private:
		friend class Window;
		static std::vector<bool> m_Keys;
		static std::vector<bool> m_MouseButtons;
		static std::vector<bool> m_KeysPrev;
		static std::vector<bool> m_MouseButtonsPrev;
		static glm::dvec2 m_Cursor;
	private:
		static std::vector<bool> AllFalse(unsigned int _count);
	protected:
		static void Keyboard(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
		static void Mouse(GLFWwindow* _window, int _button, int _action, int _mods);
		static void Cursor(GLFWwindow* _window, double _xpos, double _ypos);
	public:
		static bool OnKeyPress(unsigned int _key);
		static bool OnKeyRelease(unsigned int _key);
		
		static bool OnMousePress(unsigned int _button);
		static bool OnMouseRelease(unsigned int _button);

		static glm::vec2 GetCursor();
	};

}}