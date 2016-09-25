#pragma once

#include <vector>
#include "graphics/mesh.h"
#include "camera.h"


namespace Heart {

	using namespace Graphics;

	class Scene {
	public:
		Scene();
		~Scene();
		void add(Mesh& mesh);
		void draw(Camera* camera);
	private:
		std::vector<Mesh*> m_Meshes;
	};

}