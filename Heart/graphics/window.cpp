#include "window.h"

#include "../input.h"
#include <GLFW\glfw3.h>

namespace Heart {
	namespace Graphics {
	
		Window::Window(const char* title, const int width, const int height)
		{
			if (glfwInit() == GLFW_FALSE)
			{
				LOG("Failed to initialize GLFW!");
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			//glViewport(0, 0, 640, 480);



			m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
			glfwMakeContextCurrent(m_Window);

			if (!m_Window)
			{
				LOG("Failed to create window!");
				glfwTerminate();
			}

			glfwSetWindowUserPointer(m_Window, this);
			glfwSetKeyCallback(m_Window, Input::keyCallback);
			glfwSetCursorPosCallback(m_Window, Input::cursorPosCallback);
			glfwSetMouseButtonCallback(m_Window, Input::mouseButtonCallback);

			//GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			//glfwSetCursor(m_Window, cursor);

			
			glewExperimental = GL_TRUE;
			glewInit();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
		
			glDepthFunc(GL_LESS);

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		};

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::clear()
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		void Window::update()
		{
			glfwSwapBuffers(m_Window);
		}

		bool Window::shouldWindowClose()
		{
			return glfwWindowShouldClose(m_Window) != 0;
		}

		vec2 Window::getCursorPosition() const
		{
			return m_CursorPosition;
		}

		void Window::cursor_position_callback(GLFWwindow* _window, double xpos, double ypos) {
			Window* window = (Window*)glfwGetWindowUserPointer(_window);
			window->m_CursorPosition.x = (float)xpos;
			window->m_CursorPosition.y = (float)ypos;
		}

		void Window::mouse_click_callback(GLFWwindow * _window, int button, int action, int mods)
		{
			Window* window = (Window*)glfwGetWindowUserPointer(_window);
			void(*f)(Window* window, int button, int action, int mods);
		}

	}
}