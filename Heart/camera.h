#pragma once

#include "object3d.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Heart {

	// Perspective camera
	class Camera : public Object3D {
	public:
		Camera(float fov, float aspect, float near, float far);
		~Camera();

		mat4 getCameraMatrix(); // Projection Matrix * View Matrix
	private:
		mat4 m_ProjectionMatrix;
	};
}