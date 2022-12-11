#pragma once

namespace NoobEngine { namespace Events {

	class Input
	{
	private:
		friend class Window;
		static glm::dvec2 m_Cursor;
		static std::vector<bool> m_Keys;
		static std::vector<bool> m_MouseButtons;
	private:
		static std::vector<bool> AllFalse(unsigned int _count);
	protected:
		static void Keyboard(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
		static void Mouse(GLFWwindow* _window, int _button, int _action, int _mods);
		static void Cursor(GLFWwindow* window, double xpos, double ypos);
	public:
		static bool GetKeyPress(unsigned int _key);
		static bool GetKeyRepeat(unsigned int _key);
		static bool GetKeyRelease(unsigned int _key);
		
		static bool GetMousePress(unsigned int _button);
		static bool GetMouseRepeat(unsigned int _button);
		static bool GetMouseRelease(unsigned int _button);

		static glm::vec2 GetCursor();
	};

}}