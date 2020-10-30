#pragma once
#include <OpenGLCore/Core/Application.h>
#include <OpenGLCore/Graphics/Program.h>
#include <OpenGLCore/Graphics/VertexArray.h>

namespace OpenGLExamples
{
	class HelloTriangleApplication : public::OpenGLCore::Application
	{
		virtual void OnEvent(OpenGLCore::Events::Event& e) override;
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;
		virtual bool Init() override;

	private:
		std::unique_ptr<OpenGLCore::Graphics::Program> m_Program;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;
	};
}