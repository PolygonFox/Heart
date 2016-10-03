#include "resourcemanager.h"

namespace Heart {

	std::vector<GLuint> ResourceManager::m_textures = std::vector<GLuint>();
	std::vector<Shader> ResourceManager::m_shaders = std::vector<Shader>();
	std::vector<Material> ResourceManager::m_materials = std::vector<Material>();


	void ResourceManager::initialise()
	{
		using namespace Resources;

		// Textures
		loadTexture(Textures::TEST, "assets/meshes/test.png");

		// Shaders
		loadShader(Shaders::BASIC, "assets/shaders/shader.vert", "assets/shaders/shader.frag");
		loadShader(Shaders::TEXTURED, "assets/shaders/shader2.vert", "assets/shaders/shader2.frag");


		// Material
		createMaterial(getShader(1));
	}

}