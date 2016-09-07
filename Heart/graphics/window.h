#pragma once

#include "../general.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Heart {
	namespace Graphics {

		class Window {
		private:
			GLFWwindow* m_Window;
		public:
			Window();
			~Window();
			void update();
			void clear();
			bool shouldWindowClose();
		};

	}
}