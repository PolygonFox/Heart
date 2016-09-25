#include "scene.h"

#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Heart {

	Scene::Scene() {

	}

	Scene::~Scene() {

	}

	void Scene::add(Mesh& mesh) {
		m_Meshes.push_back(&mesh);
	}

	void Scene::draw(Camera* camera) {

		for (int i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i]->updateMatrix();
			camera->updateMatrix();

			// Calculate MVP
			mat4 MVP = camera->getCameraMatrix() * m_Meshes[i]->getMatrix();
			glUniformMatrix4fv(m_Meshes[i]->getShader()->getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(MVP));
			m_Meshes[i]->draw();
		}
	}
}