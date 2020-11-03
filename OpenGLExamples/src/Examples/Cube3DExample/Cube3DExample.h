#pragma once
#include "Examples/Example.h"

#include <memory>
#include <OpenGLCore/Graphics/Shader.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <OpenGLCore/Graphics/Texture2D.h>
#include <OpenGLCore/Utility/Camera.h>

#include <OpenGLCore/Events/ApplicationEvent.h>

namespace OpenGLExamples
{
	class Cube3DExample : public Example
	{
	public :
		~Cube3DExample() override;

	protected:
		virtual void Init() override;
		virtual void OnEvent(OpenGLCore::Events::Event& e) override;
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;
		virtual void ImGuiRender() override;

	private:
		bool OnWindowResize(OpenGLCore::Events::WindowResizeEvent& e);

	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

		std::unique_ptr<OpenGLCore::Graphics::Shader> m_Shader;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_Texture;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_Texture2;
		std::unique_ptr<OpenGLCore::Utility::Camera> m_Camera;
	};
}