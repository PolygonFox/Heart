#pragma once

#include "../general.h"
#include <GL\glew.h>


namespace Heart {
	namespace Graphics {

		class Shader {
		public:
			Shader(const char* vertexSourcePath, const char* fragmentSourcePath);
			~Shader();
			void use();
			GLuint getUniformLocation(char* name);
		private:
			GLuint m_Program;
		};
	}
}