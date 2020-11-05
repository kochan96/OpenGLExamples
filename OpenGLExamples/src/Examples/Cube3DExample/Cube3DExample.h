#pragma once
#include "Examples/Example.h"

#include <memory>
#include <OpenGLCore/Graphics/Shader.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <OpenGLCore/Graphics/Texture2D.h>
#include <OpenGLCore/Utility/CameraController.h>

#include <OpenGLCore/Events/ApplicationEvent.h>

namespace OpenGLExamples
{
	class Cube3DExample : public Example
	{
	protected:
		virtual void Init() override;
		virtual void OnEvent(OpenGLCore::Events::Event& e) override;
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;

	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

		std::unique_ptr<OpenGLCore::Graphics::Shader> m_Shader;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_Texture;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_Texture2;
		std::unique_ptr<OpenGLCore::Utility::CameraController> m_CameraController;
	};
}