#pragma once

#include "../general.h"

#include <GL\glew.h>
#include <vector>


namespace Heart {
	namespace Graphics {

		struct Geometry {
			Geometry() {

			}
			Geometry(std::vector<Vertex> vertices, std::vector<GLuint> indices)
			:vertices(vertices), indices(indices) {
				//
			}
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;

			void add(Geometry geo)
			{
				int offset = vertices.size();
				vertices.insert(vertices.end(), geo.vertices.begin(), geo.vertices.end());
				indices.insert(indices.end(), geo.indices.begin(), geo.indices.end());
				for (int i = 0; i < geo.indices.size(); i++)
				{
					indices.push_back(offset + geo.indices[i]);
				}
			}

			void applyMatrix(mat4 matrix)
			{
				for (int i = 0; i < vertices.size(); i++)
					vertices[i].position = vec3(vec4(vertices[i].position, 1.0f) * matrix);
			}
		};
	}
}
