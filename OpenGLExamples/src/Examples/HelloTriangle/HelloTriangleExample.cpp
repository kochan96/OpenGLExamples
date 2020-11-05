#include "HelloTriangleExample.h"
#include <OpenGLCore/Graphics/RendererAPI.h>

namespace OpenGLExamples
{
	void HelloTriangleExample::Init()
	{
		OpenGLCore::Graphics::RendererAPI::Disable(OpenGLCore::Graphics::Capability::DepthTest);

		float vertices[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.0f,0.5f
		};

		m_Shader = std::make_unique<OpenGLCore::Graphics::Shader>(
			"assets/shaders/HelloTriangleExample/helloTriangle.vert",
			"assets/shaders/HelloTriangleExample/helloTriangle.frag");

		OpenGLCore::Graphics::RendererAPI::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);


		m_VertexArray = std::make_unique<OpenGLCore::Graphics::VertexArray>();
		auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_Position"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		m_Shader->Use();
		m_Shader->SetFloat3("u_Color", m_RectangleColor);

		m_VertexArray->Bind();
	}

	void HelloTriangleExample::ImGuiRender()
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

	void HelloTriangleExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		OpenGLCore::Graphics::RendererAPI::Clear(OpenGLCore::Graphics::BufferBit::Color);

		OpenGLCore::Graphics::RendererAPI::DrawArrays(OpenGLCore::Graphics::PrimitiveType::Triangles, 0, 3);
	}
}
