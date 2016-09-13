#pragma once

#include "../general.h"
#include <GL\glew.h>
#include <map>

namespace Heart {
	namespace Graphics {

		class Shader {
		public:
			Shader(const char* vertexSourcePath, const char* fragmentSourcePath);
			~Shader();
			void use();
			GLuint getUniformLocation(char* name);
		private:
			std::map<char*, GLint> m_uniformLocations;
			GLuint m_Program;
		};
	}
}