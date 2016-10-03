#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Heart {

	class Object3D {
	public:
		void setPosition(float x, float y, float z);
		void setPosition(const vec3& position);
		vec3 getPosition() const;

		void setScale(float x, float y, float z);
		void setScale(vec3 scale);

		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);

		void updateMatrix();
		mat4 getMatrix() const;
		
	private:
		vec3 m_Position;
		vec3 m_Rotation;
		vec3 m_Scale = vec3(1,1,1);

		mat4 m_Matrix;
	};
}