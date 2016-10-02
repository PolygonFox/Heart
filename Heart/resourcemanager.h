#pragma once

#include <GL\glew.h>
#include <vector>
#include <SOIL.h>

#include "graphics\mesh.h"
#include "graphics\shader.h"
#include "graphics\geometry.h"
#include "materials\material.h"

namespace Heart {

	namespace Resources {
		enum Shaders {
			BASIC,
			TEXTURED
		};
		enum Textures {
			TEST
		};
	}

	class ResourceManager {
	public:
		static void initialise();
		static GLuint getTexture(int id) { return m_textures[id]; }
		static Shader* getShader(int id) { return  &m_shaders[id]; };
		static Material* getMaterial(int id) { return &m_materials[id]; }

		static void loadTexture(const int id, const char* path)
		{
			GLuint texture_id;
			int width, height;
			unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			SOIL_free_image_data(image);

			m_textures.push_back(texture_id);
		}

		static void loadShader(const int id, const char* vertexPath, const char* fragmentPath)
		{
			m_shaders.push_back(Shader(vertexPath, fragmentPath));
		}

		static void createMaterial(Shader* shader) 
		{
			m_materials.push_back(Material(shader));
		}

	private:
		static std::vector<GLuint> m_textures;
		static std::vector<Shader> m_shaders;
		static std::vector<Material> m_materials;
	};

}