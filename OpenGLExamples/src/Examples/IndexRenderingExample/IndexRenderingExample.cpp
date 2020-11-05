#include "IndexRenderingExample.h"
#include <OpenGLCore/Graphics/RendererAPI.h>


namespace OpenGLExamples
{
	void IndexRenderingExample::Init()
	{
		OpenGLCore::Graphics::RendererAPI::Disable(OpenGLCore::Graphics::Capability::DepthTest);

		float vertices[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,0.5f,
		};

		m_Shader = std::make_unique<OpenGLCore::Graphics::Shader>(
			"assets/shaders/IndexRenderingExample/indexRendering.vert",
			"assets/shaders/IndexRenderingExample/indexRendering.frag");

		OpenGLCore::Graphics::RendererAPI::SetClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);

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

		m_Shader->Use();
		m_Shader->SetFloat3("u_Color", m_RectangleColor);

		m_VertexArray->Bind();
	}

	void IndexRenderingExample::ImGuiRender()
	{
		if (ImGui::Begin("Settings"))
		{
			if (ImGui::ColorEdit3("Clear Color", &m_ClearColor.x))
			{
				OpenGLCore::Graphics::RendererAPI::SetClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);
			}

			if (ImGui::ColorEdit3("Rectangle Color", &m_RectangleColor.x))
			{
				m_Shader->SetFloat3("u_Color", m_RectangleColor);
			}
		}

		ImGui::End();
	}

	void IndexRenderingExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		OpenGLCore::Graphics::RendererAPI::Clear(OpenGLCore::Graphics::BufferBit::Color);

		OpenGLCore::Graphics::RendererAPI::DrawIndexed(
			OpenGLCore::Graphics::PrimitiveType::Triangles,
			OpenGLCore::Graphics::IndexType::UnsignedInt,
			m_VertexArray->GetIndexBuffer()->GetCount());
	}
}
