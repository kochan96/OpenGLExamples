#include "LightsExamples.h"

#include <OpenGLCore/Graphics/RendererAPI.h>
#include <OpenGLCore/Core/Application.h>

namespace OpenGLExamples
{
	LightsExamples::~LightsExamples()
	{
		OpenGLCore::Graphics::RendererAPI::Disable(OpenGLCore::Graphics::Capability::DepthTest);
	}

	void LightsExamples::Init()
	{
		m_Camera = std::make_unique<OpenGLCore::Utility::Camera>();
		auto& window = OpenGLCore::Application::Get().GetMainWindow();

		m_Camera->SetProjectionType(OpenGLCore::Utility::ProjectionType::Perspective);
		m_Camera->GetTransform().m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

		float vertices[] = {
			//positions			  //texture
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	void LightsExamples::OnEvent(OpenGLCore::Events::Event& e)
	{
		OpenGLCore::Events::EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<OpenGLCore::Events::WindowResizeEvent>(
			std::bind(&LightsExamples::OnWindowResize, this, std::placeholders::_1));
	}

	void LightsExamples::OnUpdate(OpenGLCore::Timestep ts)
	{
		OpenGLCore::Graphics::RendererAPI::Clear(
			OpenGLCore::Graphics::BufferBit::Color
			| OpenGLCore::Graphics::BufferBit::Depth);

		m_ModelMatrix = glm::rotate(m_ModelMatrix, ts * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		const auto viewMatrix = m_Camera->GetViewMatrix();
		const auto& projectionMatrix = m_Camera->GetProjection();

		m_Shader->SetMat4("u_ModelViewProjection", projectionMatrix * viewMatrix * m_ModelMatrix);

		OpenGLCore::Graphics::RendererAPI::DrawArrays(
			OpenGLCore::Graphics::PrimitiveType::Triangles,
			0,
			36);
	}

	void LightsExamples::ImGuiRender()
	{
		if (ImGui::Begin("Camera"))
		{
			auto& transform = m_Camera->GetTransform();

			ImGui::DragFloat3("Translation", &transform.m_Position.x, 0.1f);

			auto rotationDegrees = glm::degrees(transform.m_Rotation);
			if (ImGui::DragFloat3("Rotation", &rotationDegrees.x))
			{
				transform.m_Rotation = glm::radians(rotationDegrees);
			}
		}

		ImGui::End();
	}

	bool LightsExamples::OnWindowResize(OpenGLCore::Events::WindowResizeEvent& e)
	{
		m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
