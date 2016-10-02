#pragma once

#include "..\graphics\shader.h"

namespace Heart {

	using namespace Graphics;

	class Material {
	public:
		Material(Shader* shader);
		void use(glm::mat4& meshMatrix);
		~Material();
	private:
		Shader* m_shader;
	};
}