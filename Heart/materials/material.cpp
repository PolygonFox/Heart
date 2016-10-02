#include "material.h"

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "../resourcemanager.h"
#include "../application.h"

namespace Heart {
	Material::Material(Shader* shader)
		: m_shader(shader)
	{
	
	}

	Material::~Material()
	{

	}

	void Material::use(glm::mat4& meshMatrix)
	{
		glm::mat4 MVP = Application::getActiveCamera()->getCameraMatrix() * meshMatrix;

		glUniformMatrix4fv(m_shader->getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform1f(m_shader->getUniformLocation("time"), Application::getTime());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(0));
		glUniform1i(m_shader->getUniformLocation("diffuse_texture"), 0);

		m_shader->use();
	}
}
