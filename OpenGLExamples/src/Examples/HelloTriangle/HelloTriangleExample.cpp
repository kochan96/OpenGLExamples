#include "HelloTriangleExample.h"
#include <OpenGLCore/Graphics/Program.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <glad/glad.h>

namespace OpenGLExamples
{
	void HelloTriangleExample::Init()
	{
		float vertices[] = {
		-1.0f,-1.0f,
		1.0f,-1.0f,
		0.0f,1.0f
		};

		OpenGLCore::Graphics::Shader vertexShader("assets/shaders/HelloTriangle/helloTriangle.vert", OpenGLCore::Graphics::ShaderType::Vertex);
		OpenGLCore::Graphics::Shader fragmentShader("assets/shaders/HelloTriangle/helloTriangle.frag", OpenGLCore::Graphics::ShaderType::Fragment);

		m_Program = std::make_unique<OpenGLCore::Graphics::Program>("Hello Triangle");
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
	}

	void HelloTriangleExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

}
