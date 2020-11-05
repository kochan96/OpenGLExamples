#include "CameraController.h"

#include <functional>
#include <glm/gtx/rotate_vector.hpp>

#include <OpenGLCore/Core/Input.h>

namespace OpenGLCore::Utility
{
	CameraController::CameraController(float fov, float nearClipPlane, float farClipPlane, unsigned int width, unsigned int height)
		:m_Fov(fov)
	{
		m_Camera.SetPerspective(fov, nearClipPlane, farClipPlane);
		m_Camera.SetProjectionType(OpenGLCore::Utility::ProjectionType::Perspective);

		OnResize(width, height);
		RecalculateViewMatrix();
	}

	glm::vec3 CameraController::GetCameraRight() const
	{
		glm::vec3 right(1.0f, 0.0f, 0.0f);
		right = glm::rotateX(right, m_CameraRotation.x);
		right = glm::rotateY(right, m_CameraRotation.y);

		return right;
	}

	glm::vec3 CameraController::GetCameraFront() const
	{
		glm::vec3 front(0.0f, 0.0f, -1.0f);
		front = glm::rotateX(front, m_CameraRotation.x);
		front = glm::rotateY(front, m_CameraRotation.y);

		return front;
	}

	glm::vec3 CameraController::GetCameraUp() const
	{
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		up = glm::rotateX(up, m_CameraRotation.x);
		up = glm::rotateY(up, m_CameraRotation.y);

		return up;
	}

	void CameraController::OnUpdate(Timestep ts)
	{

		bool changed = false;

		float translationSpeed = m_CameraTranslationSpeed;
		if (Input::IsKeyPressed(OGLC_KEY_LEFT_SHIFT))
		{
			translationSpeed *= 10;
		}

		if (Input::IsKeyPressed(OGLC_KEY_A))
		{
			changed = true;
			m_CameraPosition -= GetCameraRight() * (translationSpeed * ts);
		}
		else if (Input::IsKeyPressed(OGLC_KEY_D))
		{
			changed = true;
			m_CameraPosition += GetCameraRight() * (translationSpeed * ts);
		}

		if (Input::IsKeyPressed(OGLC_KEY_W))
		{
			changed = true;
			m_CameraPosition += GetCameraFront() * (translationSpeed * ts);
		}
		else if (Input::IsKeyPressed(OGLC_KEY_S))
		{
			changed = true;
			m_CameraPosition -= GetCameraFront() * (translationSpeed * ts);
		}

		if (Input::IsKeyPressed(OGLC_KEY_Q))
		{
			changed = true;
			m_CameraPosition += GetCameraUp() * (translationSpeed * ts);
		}
		else if (Input::IsKeyPressed(OGLC_KEY_E))
		{
			changed = true;
			m_CameraPosition -= GetCameraUp() * (translationSpeed * ts);
		}

		changed |= HandleRotation(ts);

		if (changed)
		{
			RecalculateViewMatrix();
		}

	}

	bool CameraController::HandleRotation(Timestep ts)
	{
		auto mousePosition = Input::GetMousePosition();

		auto maxX = glm::radians(89.0f);
		auto minX = glm::radians(-89.0f);

		bool changed = false;

		if (Input::IsMouseButtonPressed(OGLC_MOUSE_BUTTON_RIGHT))
		{
			m_CameraRotation.x -= (mousePosition.y - lastMousePos.y) * m_CameraRotationSpeed;
			m_CameraRotation.y -= (mousePosition.x - lastMousePos.x) * m_CameraRotationSpeed;

			if (m_CameraRotation.x > maxX)
				m_CameraRotation.x = maxX;
			if (m_CameraRotation.x < minX)
				m_CameraRotation.x = minX;

			changed = true;
		}

		lastMousePos = mousePosition;
		return changed;
	}

	void CameraController::RecalculateViewMatrix()
	{
		glm::vec3 front = GetCameraFront();

		m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + front, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void CameraController::OnEvent(Events::Event& e)
	{
		Events::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Events::MouseScrolledEvent>(
			std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<Events::WindowResizeEvent>(
			std::bind(&CameraController::OnWindowResized, this, std::placeholders::_1));
	}

	void CameraController::OnResize(float width, float height)
	{
		m_Camera.SetViewportSize(width, height);
	}

	bool CameraController::OnMouseScrolled(Events::MouseScrolledEvent& e)
	{
		m_Fov -= (float)e.GetYOffset();
		if (m_Fov < 1.0f)
			m_Fov = 1.0f;
		if (m_Fov > 120.0f)
			m_Fov = 120.0f;

		m_Camera.SetPerspectiveVerticalFOV(m_Fov);

		return false;
	}

	bool CameraController::OnWindowResized(Events::WindowResizeEvent& e)
	{
		//HZ_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}
