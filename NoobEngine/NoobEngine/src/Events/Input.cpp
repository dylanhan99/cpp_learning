#include "nepch.h"
#include "Input.h"

namespace NoobEngine { namespace Events {

	std::vector<bool> Input::m_Keys				= Input::AllFalse(GLFW_KEY_LAST);
	std::vector<bool> Input::m_MouseButtons		= Input::AllFalse(GLFW_MOUSE_BUTTON_LAST);
	std::vector<bool> Input::m_KeysPrev			= m_Keys;
	std::vector<bool> Input::m_MouseButtonsPrev = m_MouseButtons;
	glm::dvec2 Input::m_Cursor					= glm::dvec2(0, 0);

	std::vector<bool> Input::AllFalse(unsigned int _count)
	{
		std::vector<bool> vec;
		for (unsigned int i = 0; i < _count; i++)
			vec.push_back(GLFW_RELEASE);
		return vec;
	}

	void Input::Keyboard(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
	{
		m_KeysPrev[_key] = m_Keys[_key];
		m_Keys[_key] = _action;
	}

	void Input::Mouse(GLFWwindow* _window, int _button, int _action, int _mods)
	{
		m_MouseButtonsPrev[_button] = m_MouseButtons[_button];
		m_MouseButtons[_button] = _action;
	}

	void Input::Cursor(GLFWwindow* _window, double _xpos, double _ypos)
	{
		m_Cursor.x = _xpos;
		m_Cursor.y = _ypos;
	}

	bool Input::OnKeyPress(unsigned int _key)
	{
		if (!(m_KeysPrev[_key] != GLFW_PRESS && m_Keys[_key] == GLFW_PRESS)) // if key within bounds
			return false;
		m_KeysPrev[_key] = m_Keys[_key];
		return true;
	}

	bool Input::OnKeyRepeat(unsigned int _key)
	{
		if (m_Keys[_key] != GLFW_PRESS) // if key within bounds
			return false;
		return true;
	}

	bool Input::OnKeyRelease(unsigned int _key)
	{
		if (!(m_KeysPrev[_key] != GLFW_RELEASE && m_Keys[_key] == GLFW_RELEASE)) // if key within bounds
			return false;
		m_KeysPrev[_key] = m_Keys[_key];
		return true;
	}

	bool Input::OnMouseClick(unsigned int _button)
	{
		if (!(m_MouseButtonsPrev[_button] != GLFW_PRESS && m_MouseButtons[_button] == GLFW_PRESS)) // if key within bounds
			return false;
		m_MouseButtonsPrev[_button] = m_MouseButtons[_button];
		return true;
	}

	bool Input::OnMouseRepeat(unsigned int _button)
	{
		if (m_MouseButtons[_button] != GLFW_PRESS) // if key within bounds
			return false;
		return true;
	}

	bool Input::OnMouseRelease(unsigned int _button)
	{
		if (!(m_MouseButtonsPrev[_button] != GLFW_RELEASE && m_MouseButtons[_button] == GLFW_RELEASE)) // if key within bounds
			return false;
		m_MouseButtonsPrev[_button] = m_MouseButtons[_button];
		return true;
	}

	glm::vec2 Input::GetCursor()
	{
		return m_Cursor;
	}

	double Input::GetCursorX()
	{
		return m_Cursor.x;
	}

	double Input::GetCursorY()
	{
		return m_Cursor.y;
	}

}}