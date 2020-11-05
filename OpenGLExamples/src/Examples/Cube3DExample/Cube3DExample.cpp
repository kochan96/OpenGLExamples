#include "Cube3DExample.h"

#include <OpenGLCore/Graphics/RendererAPI.h>
#include <OpenGLCore/Core/Application.h>

#include <glad/glad.h>

namespace OpenGLExamples
{
	void Cube3DExample::Init()
	{
		auto& window = OpenGLCore::Application::Get().GetMainWindow();

		constexpr float fov = glm::radians(45.0f);
		float nearClip = 0.01f;
		float farClip = 1000.0f;
		unsigned int width = window.GetWidth();
		unsigned int height = window.GetHeight();

		m_CameraController = std::make_unique<OpenGLCore::Utility::CameraController>(
			glm::radians(45.0f),
			nearClip,
			farClip,
			width,
			height);

		float vertices[] = {
			// back face
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
			// front face
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
			// left face
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
			// right face
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
			// bottom face          
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
			// top face
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left              
		};

		m_Shader = std::make_unique<OpenGLCore::Graphics::Shader>(
			"assets/shaders/Cube3DExample/cube3DExample.vert",
			"assets/shaders/Cube3DExample/cube3DExample.frag");

		m_VertexArray = std::make_unique<OpenGLCore::Graphics::VertexArray>();
		auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{OpenGLCore::Graphics::ShaderDataType::Float3,"a_Position"},
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_TextureCoord"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		m_Shader->Use();
		const int textureIndex = 1;
		const int textureIndex2 = 2;

		m_Shader->SetInt("u_TextureSampler", textureIndex);
		m_Shader->SetInt("u_TextureSampler2", textureIndex2);


		m_Texture = std::make_unique<OpenGLCore::Graphics::Texture2D>("assets/textures/container.jpg");

		m_Texture2 = std::make_unique<OpenGLCore::Graphics::Texture2D>("assets/textures/awesomeface.png");
		
		m_Texture->Bind(textureIndex);
		m_Texture2->Bind(textureIndex2);

		m_VertexArray->Bind();
		OpenGLCore::Graphics::RendererAPI::Enable(OpenGLCore::Graphics::Capability::DepthTest);
	}

	void Cube3DExample::OnEvent(OpenGLCore::Events::Event& e)
	{
		m_CameraController->OnEvent(e);
	}

	void Cube3DExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		m_CameraController->OnUpdate(ts);

		OpenGLCore::Graphics::RendererAPI::Clear(
			OpenGLCore::Graphics::BufferBit::Color
			| OpenGLCore::Graphics::BufferBit::Depth);

		//m_ModelMatrix = glm::rotate(m_ModelMatrix, ts * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		const auto& viewMatrix = m_CameraController->GetViewMatrix();
		const auto& projectionMatrix = m_CameraController->GetProjectionMatrix();

		m_Shader->SetMat4("u_ModelViewProjection", projectionMatrix * viewMatrix * m_ModelMatrix);

		OpenGLCore::Graphics::RendererAPI::DrawArrays(
			OpenGLCore::Graphics::PrimitiveType::Triangles,
			0,
			36);
	}
}
