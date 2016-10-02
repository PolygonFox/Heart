#pragma once

#include "../object3d.h"


#include <GL\glew.h>
#include <vector>
#include "geometry.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "../materials/material.h"

namespace Heart {
	namespace Graphics {

		class Mesh : public Object3D {
		public:

			Mesh(const char* fileName, Material* material);
			Mesh(Geometry& geometry, Material* material);
			~Mesh();
			void draw();
			static Geometry getGeometry(const char* fileName);
			Material* getMaterial();
		private:
			int m_numIndices;
			GLuint m_VAO;
			Material* m_material;
		};
	}
}