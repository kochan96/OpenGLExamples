#include "TextureRenderingExample.h"

#include <OpenGLCore/Graphics/RendererAPI.h>
#include <stb_image.h>
#include <glad/glad.h>

namespace OpenGLExamples
{
	TextureRenderingExample::~TextureRenderingExample()
	{
		glDeleteTextures(1, &m_TextureId);
	}

	void TextureRenderingExample::Init()
	{
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

		//Create Texture
		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char* data = stbi_load("assets/textures/wall.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{

			LOG_CLIENT_ERROR("Failed to load texture");
		}

		stbi_image_free(data);


		glActiveTexture(GL_TEXTURE0 + textureIndex);
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
