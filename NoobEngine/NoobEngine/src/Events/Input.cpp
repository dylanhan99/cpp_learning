#include "nepch.h"
#include "Input.h"

namespace NoobEngine { namespace Events {

	glm::dvec2 Input::m_Cursor				= glm::dvec2(0, 0);
	std::vector<bool> Input::m_Keys			= Input::AllFalse(GLFW_KEY_LAST);
	std::vector<bool> Input::m_MouseButtons = Input::AllFalse(GLFW_MOUSE_BUTTON_LAST);

	std::vector<bool> Input::AllFalse(unsigned int _count)
	{
		std::vector<bool> vec;
		for (unsigned int i = 0; i < _count; i++)
			vec.push_back(GLFW_RELEASE);
		return vec;
	}

	void Input::Keyboard(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
	{
		std::cout << _key << "\t" << _scancode << "\t" << _action << "\t" << _mods << std::endl;
	}

	void Input::Mouse(GLFWwindow* _window, int _button, int _action, int _mods)
	{
		std::cout << _button << "\t" << _action << "\t" << _mods << std::endl;
	}

	void Input::Cursor(GLFWwindow* window, double xpos, double ypos)
	{
		std::cout << xpos << "\t" << ypos << std::endl;
	}

	bool Input::GetKeyPress(unsigned int _key)
	{
		return false;
	}

	bool Input::GetKeyRepeat(unsigned int _key)
	{
		return false;
	}

	bool Input::GetKeyRelease(unsigned int _key)
	{
		return false;
	}

	bool Input::GetMousePress(unsigned int _button)
	{
		return false;
	}

	bool Input::GetMouseRepeat(unsigned int _button)
	{
		return false;
	}

	bool Input::GetMouseRelease(unsigned int _button)
	{
		return false;
	}

	glm::vec2 Input::GetCursor()
	{
		return m_Cursor;
	}

}}