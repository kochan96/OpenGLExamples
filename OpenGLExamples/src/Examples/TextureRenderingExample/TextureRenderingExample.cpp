#include "TextureRenderingExample.h"

#include <OpenGLCore/Graphics/RendererAPI.h>
#include <stb_image.h>
#include <glad/glad.h>

namespace OpenGLExamples
{
	void TextureRenderingExample::Init()
	{
		OpenGLCore::Graphics::RendererAPI::Disable(OpenGLCore::Graphics::Capability::DepthTest);

		float vertices[] = {

			//positions   //texture
			-0.5f,-0.5f,  0.0f, 0.0f,
			0.5f,-0.5f,   1.0f, 0.0f,
			0.5f,0.5f,    1.0f, 1.0f,
			-0.5f,0.5f,   0.0f, 1.0f
		};

		m_Shader = std::make_unique<OpenGLCore::Graphics::Shader>(
			"assets/shaders/TextureRenderingExample/textureRendering.vert",
			"assets/shaders/TextureRenderingExample/textureRendering.frag");

		OpenGLCore::Graphics::RendererAPI::SetClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);

		m_VertexArray = std::make_unique<OpenGLCore::Graphics::VertexArray>();
		auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_Position"},
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_TextureCoord"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		auto indexBuffer = std::make_shared<OpenGLCore::Graphics::IndexBuffer>(indices, 6);

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader->Use();
		const int textureIndex = 0;

		m_Shader->SetInt("u_TextureSampler", textureIndex);

		m_VertexArray->Bind();

		m_Texture = std::make_unique<OpenGLCore::Graphics::Texture2D>("assets/textures/wall.jpg");
		m_Texture->Bind(textureIndex);
	}

	void TextureRenderingExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		OpenGLCore::Graphics::RendererAPI::Clear(OpenGLCore::Graphics::BufferBit::Color);

		OpenGLCore::Graphics::RendererAPI::DrawIndexed(
			OpenGLCore::Graphics::PrimitiveType::Triangles,
			OpenGLCore::Graphics::IndexType::UnsignedInt,
			m_VertexArray->GetIndexBuffer()->GetCount());
	}
}
