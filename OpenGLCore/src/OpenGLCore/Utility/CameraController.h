#pragma once
#include "Camera.h"
#include "OpenGLCore/Core/Timestep.h"
#include "OpenGLCore/Events/ApplicationEvent.h"
#include "OpenGLCore/Events/MouseEvent.h"


namespace OpenGLCore::Utility
{
	class CameraController
	{
	public:
		CameraController(float fov, float nearClipPlane, float farClipPlane, unsigned int width, unsigned int height);

		void OnUpdate(Timestep ts);

		void OnEvent(Events::Event& e);

		void OnResize(float width, float height);

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_Camera.GetProjection(); }

		const glm::vec3& GetCameraPosition() const { return m_CameraPosition; }

		glm::vec3 GetCameraRight() const;
		glm::vec3 GetCameraUp() const;
		glm::vec3 GetCameraFront() const;

	private:
		bool HandleRotation(Timestep ts);

		bool OnMouseScrolled(Events::MouseScrolledEvent& e);
		bool OnWindowResized(Events::WindowResizeEvent& e);

		void RecalculateViewMatrix();

	private:
		float m_Fov;
		Camera m_Camera;
		
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		glm::vec3 m_CameraPosition = { 0.0f,0.0f,3.0f };
		glm::vec2 m_CameraRotation = { 0.0f,0.0f };
		glm::vec2 lastMousePos = { 0.0f,0.0f };

		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 0.03f;
	};
}