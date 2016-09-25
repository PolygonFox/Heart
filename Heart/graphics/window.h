#pragma once

#include "../general.h"

#include "../scene.h"
#include "../camera.h"

#include "../application.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>

namespace Heart {
	namespace Graphics {

		using namespace glm;

		class Window {

		private:
			GLFWwindow* m_Window;
			vec2 m_CursorPosition;
			static void cursor_position_callback(GLFWwindow* _window, double xpos, double ypos);
			static void mouse_click_callback(GLFWwindow* _window, int button, int action, int mods);

		public:
			Window(const char* title, const int width, const int height);
			~Window();
			void update();
			void clear();
			bool shouldWindowClose();
			vec2 getCursorPosition() const;			
		};

	}
}