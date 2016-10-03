#include "scene.h"

#include "resourcemanager.h"
#include "input.h"

namespace Heart {


	Scene::Scene() {

	}
	Scene::~Scene() {

	}

	void Scene::add(Mesh mesh) {
		m_Meshes.push_back(mesh);
	}


	void Scene::draw(Camera* camera) {

		//LOG(Input::getAxis(MOUSE_X));
		for (int i = 0; i < m_Meshes.size(); i++)
		{
		//	m_Meshes[i].rotateX(0.01 * Input::getAxis(MOUSE_X));
		//	m_Meshes[i].rotateY(0.01 * Input::getAxis(MOUSE_Y));
			m_Meshes[i].updateMatrix();
			camera->updateMatrix();
			m_Meshes[i].draw();
		}
	}
}