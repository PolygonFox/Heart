#include "input.h"

namespace Heart {



	bool Input::m_keys[1024];
	bool Input::m_mouseButtons[8];
	double Input::m_mousePositionX = 0.1;
	double Input::m_mousePositionY = 0.1;
	double Input::m_axes[sizeof(Axis)];
	
	void Input::initialise()
	{
		for (int i = 0; i < sizeof(m_keys); i++)
			m_keys[i] = false;

		for (int i = 0; i < sizeof(m_mouseButtons); i++)
			m_mouseButtons[i] = false;
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_keys[key] = action != GLFW_RELEASE;
	}

	void Input::cursorPosCallback(GLFWwindow * _window, double xpos, double ypos)
	{
		LOG(xpos - m_mousePositionX);
		m_axes[MOUSE_X] = xpos - m_mousePositionX;
		m_axes[MOUSE_Y] = ypos - m_mousePositionY;
		m_mousePositionX = xpos;
		m_mousePositionY = ypos;
	}

	void Input::mouseButtonCallback(GLFWwindow * _window, int button, int action, int mods)
	{
		m_mouseButtons[button] = action != GLFW_RELEASE;
	}

	bool Input::isKeyDown(int keyCode)
	{
		return m_keys[keyCode];
	}

	bool Input::isMouseButtonDown(int buttonCode)
	{
		return m_mouseButtons[buttonCode];
	}

	double Input::getAxis(Axis axis)
	{
		return m_axes[axis];
	}

	void Input::update()
	{
		// Reset axis values
		for (int i = 0; i < sizeof(m_axes); i++)
			m_axes[i] = 0.0;
	}

}