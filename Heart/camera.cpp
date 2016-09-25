#include "camera.h"

namespace Heart {

	Camera::Camera(float fov, float aspect, float near, float far)
	{
		m_ProjectionMatrix = glm::perspective(fov, aspect, near, far);
	}

	Camera::~Camera()
	{
	}

	mat4 Camera::getCameraMatrix()
	{
		return m_ProjectionMatrix * this->getMatrix();
	}
}
