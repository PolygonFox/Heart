#include "window.h"

#include <GLFW\glfw3.h>

namespace Heart {
	namespace Graphics {
	
		Window::Window() 
		{
			if (glfwInit() == GLFW_FALSE)
			{
				LOG("Failed to initialize GLFW!");
			}

			//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			//glViewport(0, 0, 640, 480);

			m_Window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
			
			if (!m_Window)
			{
				LOG("Failed to create window!");
				glfwTerminate();
			}

			glfwMakeContextCurrent(m_Window);
			
			glewExperimental = GL_TRUE;
			glewInit();

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glClearColor(0.2f, 0.5f, 0.2f, 1.0f);
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
	}
}