#include "object3d.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\euler_angles.hpp>

namespace Heart {
	void Object3D::setPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}

	void Object3D::setPosition(const vec3& position)
	{
		m_Position.x = position.x;
		m_Position.y = position.y;
		m_Position.z = position.z;
	}

	vec3 Object3D::getPosition() const
	{
		return m_Position;
	}

	void Object3D::setScale(float x, float y, float z)
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Scale.z = z;
	}

	void Object3D::setScale(vec3 scale)
	{
		m_Scale = scale;
	}

	void Object3D::rotateX(float angle)
	{
		m_Rotation.x += angle;
	}

	void Object3D::rotateY(float angle)
	{
		m_Rotation.y += angle;
	}

	void Object3D::rotateZ(float angle)
	{
		m_Rotation.z += angle;
	}

	void Object3D::updateMatrix()
	{
		mat4 mat;
		mat = glm::scale(mat, m_Scale);
		mat = glm::translate(mat, m_Position);
		mat *= glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		m_Matrix = mat;
	}

	mat4 Object3D::getMatrix() const
	{
		return m_Matrix;
	}
}