#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace OpenGLCore::Utility
{
	Camera::Camera()
	{
		RecalculateProjectection();
	}

	void Camera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		RecalculateProjectection();
	}

	void Camera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateProjectection();
	}

	void Camera::SetViewportSize(unsigned int width, unsigned int height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjectection();
	}

	void Camera::RecalculateProjectection()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;

			m_Projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}

	}
}
