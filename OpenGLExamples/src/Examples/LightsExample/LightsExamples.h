#pragma once
#include "Examples/Example.h"

#include <memory>
#include <glm/glm.hpp>
#include <vector>

#include <OpenGLCore/Graphics/Shader.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <OpenGLCore/Graphics/Texture2D.h>
#include <OpenGLCore/Utility/CameraController.h>
#include <OpenGLCore/Utility/Lights.h>

#include <OpenGLCore/Events/ApplicationEvent.h>


namespace OpenGLExamples
{
	class LightsExample : public Example
	{
	protected:
		virtual void Init() override;
		virtual void OnEvent(OpenGLCore::Events::Event& e) override;
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;

	private:
		std::unique_ptr<OpenGLCore::Graphics::Shader> m_Shader;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_DiffuseTexture;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_SpecularTexture;
		std::unique_ptr<OpenGLCore::Utility::CameraController> m_CameraController;

		OpenGLCore::Utility::DirLight m_DirLight;
		std::vector<OpenGLCore::Utility::PointLight> m_PointLights;
		OpenGLCore::Utility::SpotLight m_SpotLight;

		std::vector<glm::vec3> m_CubePositions;
	};
}

