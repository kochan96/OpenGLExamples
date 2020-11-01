#include "IndexRenderingExample.h"

#include <glad/glad.h>

namespace OpenGLExamples
{
	void IndexRenderingExample::Init()
	{
		float vertices[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,0.5f,
		};

		OpenGLCore::Graphics::Shader vertexShader("assets/shaders/HelloTriangle/helloTriangle.vert", OpenGLCore::Graphics::ShaderType::Vertex);
		OpenGLCore::Graphics::Shader fragmentShader("assets/shaders/HelloTriangle/helloTriangle.frag", OpenGLCore::Graphics::ShaderType::Fragment);

		m_Program = std::make_unique<OpenGLCore::Graphics::Program>("Index Rendering");
		m_Program->Create({ vertexShader,fragmentShader });

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		m_VertexArray = std::make_unique<OpenGLCore::Graphics::VertexArray>();
		auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_Position"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		auto indexBuffer = std::make_shared<OpenGLCore::Graphics::IndexBuffer>(indices, 6);

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Program->Use();
		m_VertexArray->Bind();
	}

	void IndexRenderingExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		m_Program->SetBool("Test", false);

		glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}
}
