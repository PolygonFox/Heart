#pragma once
#include "general.h"

#include <GLFW\glfw3.h>

namespace Heart {

	enum Axis {
		HORIZONTAL,
		VERTICAL,
		MOUSE_X,
		MOUSE_Y
	};

	class Input {
	public:
		static void initialise();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursorPosCallback(GLFWwindow* _window, double xpos, double ypos);
		static void mouseButtonCallback(GLFWwindow * _window, int button, int action, int mods);

		static bool isKeyDown(int keyCode);
		static bool isMouseButtonDown(int buttonCode);
		
		static double getAxis(Axis axis);


		static void update();

	private:
		static bool m_keys[];
		static double m_axes[];
		static bool m_mouseButtons[];
		static double m_mousePositionX;
		static double m_mousePositionY;
	};
}