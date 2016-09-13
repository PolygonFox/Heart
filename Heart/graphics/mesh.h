#pragma once

#include "shader.h"
#include <GL\glew.h>


#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Heart {
	namespace Graphics {


		class Mesh {
		public:

			Mesh(const char* fileName, Shader* shader);
			~Mesh();
			void draw();
		private:
			int m_numIndices;
			GLuint m_VAO;
			Shader* m_Shader;
		};
	}
}