#include "HelloTriangleApplication.h"
#include <OpenGLCore/Graphics/Program.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <glad/glad.h>

namespace OpenGLExamples
{
	bool HelloTriangleApplication::Init()
	{
		Application::Init();

		float vertices[] = {
		-1.0f,-1.0f,
		1.0f,-1.0f,
		0.0f,1.0f
		};

		OpenGLCore::Graphics::Shader vertexShader("assets/simpleShader.vert", OpenGLCore::Graphics::ShaderType::Vertex);
		OpenGLCore::Graphics::Shader fragmentShader("assets/simpleShader.frag", OpenGLCore::Graphics::ShaderType::Fragment);

		m_Program = std::make_unique<OpenGLCore::Graphics::Program>();
		m_Program->Create({ vertexShader,fragmentShader });

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		m_VertexArray = std::make_unique<OpenGLCore::Graphics::VertexArray>();
		auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_Position"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		m_Program->Use();
		m_VertexArray->Bind();

		return true;
	}

	void HelloTriangleApplication::OnUpdate(OpenGLCore::Timestep ts)
	{
		Application::OnUpdate(ts);

		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void HelloTriangleApplication::OnEvent(OpenGLCore::Events::Event& e)
	{
		Application::OnEvent(e);
	}
}
