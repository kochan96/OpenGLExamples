#include "LightsExamples.h"

#include <OpenGLCore/Graphics/RendererAPI.h>
#include <OpenGLCore/Core/Application.h>
#include <OpenGLCore/Utility/Material.h>

namespace OpenGLExamples
{
	void LightsExample::Init()
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
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};

		m_Shader = std::make_unique<OpenGLCore::Graphics::Shader>(
			"assets/shaders/LightsExample/lightsExample.vert",
			"assets/shaders/LightsExample/lightsExample.frag");

		m_VertexArray = std::make_unique<OpenGLCore::Graphics::VertexArray>();
		auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{OpenGLCore::Graphics::ShaderDataType::Float3,"a_Position"},
			{OpenGLCore::Graphics::ShaderDataType::Float3,"a_Normal"},
			{OpenGLCore::Graphics::ShaderDataType::Float2,"a_TextureCoord"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		m_Shader->Use();

		OpenGLCore::Utility::Material material;
		material.DiffuseTextureSlot = 0;
		material.SpecularTextureSlot = 1;
		material.Shininess = 32.0f;

		m_Shader->SetInt("u_Material.Diffuse", material.DiffuseTextureSlot);
		m_Shader->SetInt("u_Material.Specular", material.SpecularTextureSlot);
		m_Shader->SetFloat("u_Material.Shininess", material.Shininess);

		m_DiffuseTexture = std::make_unique<OpenGLCore::Graphics::Texture2D>("assets/textures/container_diffuse.png");
		m_SpecularTexture = std::make_unique<OpenGLCore::Graphics::Texture2D>("assets/textures/container_specular.png");

		m_DiffuseTexture->Bind(material.DiffuseTextureSlot);
		m_SpecularTexture->Bind(material.SpecularTextureSlot);

		m_VertexArray->Bind();
		OpenGLCore::Graphics::RendererAPI::Enable(OpenGLCore::Graphics::Capability::DepthTest);

		//LIGHTS
		m_DirLight.Ambient = { 0.05f, 0.05f, 0.05f };
		m_DirLight.Diffuse = { 0.4f, 0.4f, 0.4f };
		m_DirLight.Direction = { -0.2f, -1.0f, -0.3f };
		m_DirLight.Specular = { 0.5f, 0.5f, 0.5f };

		//Point light 1
		OpenGLCore::Utility::PointLight pointLight1;
		pointLight1.Ambient = { 0.05f, 0.05f, 0.05f };
		pointLight1.Diffuse = { 0.8f, 0.8f, 0.8f };
		pointLight1.Specular = { 1.0f, 1.0f, 1.0f };
		pointLight1.Constant = 1.0f;
		pointLight1.Linear = 0.09f;
		pointLight1.Quadratic = 0.032f;
		pointLight1.Positon = { 0.7f, 0.2f, 2.0f };

		m_PointLights.push_back(pointLight1);

		//Point light 2
		OpenGLCore::Utility::PointLight pointLight2;
		pointLight2.Ambient = { 0.05f, 0.05f, 0.05f };
		pointLight2.Diffuse = { 0.8f, 0.8f, 0.8f };
		pointLight2.Specular = { 1.0f, 1.0f, 1.0f };
		pointLight2.Constant = 1.0f;
		pointLight2.Linear = 0.09f;
		pointLight2.Quadratic = 0.032f;
		pointLight2.Positon = { 2.3f, -3.3f, -4.0f };

		//m_PointLights.push_back(pointLight2);

		//Point light 3
		OpenGLCore::Utility::PointLight pointLight3;
		pointLight3.Ambient = { 0.05f, 0.05f, 0.05f };
		pointLight3.Diffuse = { 0.8f, 0.8f, 0.8f };
		pointLight3.Specular = { 1.0f, 1.0f, 1.0f };
		pointLight3.Constant = 1.0f;
		pointLight3.Linear = 0.09f;
		pointLight3.Quadratic = 0.032f;
		pointLight3.Positon = { -4.0f, 2.0f, -12.0f };

		//m_PointLights.push_back(pointLight3);

		//Point light 4
		OpenGLCore::Utility::PointLight pointLight4;
		pointLight4.Ambient = { 0.05f, 0.05f, 0.05f };
		pointLight4.Diffuse = { 0.8f, 0.8f, 0.8f };
		pointLight4.Specular = { 1.0f, 1.0f, 1.0f };
		pointLight4.Constant = 1.0f;
		pointLight4.Linear = 0.09f;
		pointLight4.Quadratic = 0.032f;
		pointLight4.Positon = { 0.0f, 0.0f, -3.0f };

		//m_PointLights.push_back(pointLight4);

		m_SpotLight.Ambient = { 0.0f, 0.0f, 0.0f };
		m_SpotLight.Diffuse = { 0.8f, 0.8f, 0.8f };
		m_SpotLight.Specular = { 1.0f, 1.0f, 1.0f };
		m_SpotLight.Constant = 1.0f;
		m_SpotLight.Linear = 0.09f;
		m_SpotLight.Quadratic = 0.032f;
		m_SpotLight.CutOff = glm::cos(glm::radians(12.5f));
		m_SpotLight.OuterCutOff = glm::cos(glm::radians(17.5f));

		//Cube positions
		m_CubePositions = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
	}

	void LightsExample::OnEvent(OpenGLCore::Events::Event& e)
	{
		m_CameraController->OnEvent(e);
	}

	static void SetDirLight(
		const OpenGLCore::Utility::DirLight& light,
		OpenGLCore::Graphics::Shader& shader)
	{
		shader.SetFloat3("u_DirLight.Direction", light.Direction);
		shader.SetFloat3("u_DirLight.Ambient", light.Ambient);
		shader.SetFloat3("u_DirLight.Diffuse", light.Diffuse);
		shader.SetFloat3("u_DirLight.Specular", light.Specular);
	}

	static void SetPointLights(
		const std::vector<OpenGLCore::Utility::PointLight>& lights,
		OpenGLCore::Graphics::Shader& shader)
	{
		shader.SetInt("u_PointLightsCount", lights.size());
		if (lights.empty())
			return;

		for (int index = 0; index < lights.size(); index++)
		{
			auto& light = lights[index];
			std::string lightName = "u_PointLights[" + std::to_string(index) + "]";
			shader.SetFloat3(lightName + ".Position", light.Positon);
			shader.SetFloat3(lightName + ".Ambient", light.Ambient);
			shader.SetFloat3(lightName + ".Diffuse", light.Diffuse);
			shader.SetFloat3(lightName + ".Specular", light.Specular);
			shader.SetBool(lightName + ".EnableAttenuation", light.EnableAttenuation);
			shader.SetBool(lightName + ".EnableAttenuation", !light.EnableAttenuation);
			shader.SetFloat(lightName + ".Constant", light.Constant);
			shader.SetFloat(lightName + ".Linear", light.Linear);
			shader.SetFloat(lightName + ".Quadratic", light.Quadratic);
		}
	}

	static void SetSpotLight(
		const OpenGLCore::Utility::SpotLight& light,
		OpenGLCore::Graphics::Shader& shader)
	{

		shader.SetFloat3("u_SpotLight.Position", light.Position);
		shader.SetFloat3("u_SpotLight.Direction", light.Direction);
		shader.SetFloat3("u_SpotLight.Ambient", light.Ambient);
		shader.SetFloat3("u_SpotLight.Diffuse", light.Diffuse);
		shader.SetFloat3("u_SpotLight.Specular", light.Specular);
		shader.SetBool("u_SpotLight.EnableAttenuation", light.EnableAttenuation);
		shader.SetFloat("u_SpotLight.Constant", light.Constant);
		shader.SetFloat("u_SpotLight.Linear", light.Linear);
		shader.SetFloat("u_SpotLight.Quadratic", light.Quadratic);
		shader.SetFloat("u_SpotLight.CutOff", light.CutOff);
		shader.SetFloat("u_SpotLight.OuterCutOff", light.OuterCutOff);
	}

	void LightsExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		m_CameraController->OnUpdate(ts);

		OpenGLCore::Graphics::RendererAPI::Clear(
			OpenGLCore::Graphics::BufferBit::Color
			| OpenGLCore::Graphics::BufferBit::Depth);

		const auto& viewMatrix = m_CameraController->GetViewMatrix();
		const auto& projectionMatrix = m_CameraController->GetProjectionMatrix();

		m_Shader->SetMat4("u_ViewMatrix", viewMatrix);
		m_Shader->SetMat4("u_ProjectionMatrix", projectionMatrix);

		auto cameraPosition = m_CameraController->GetCameraPosition();
		m_Shader->SetFloat3("u_ViewPos", cameraPosition);

		m_SpotLight.Position = cameraPosition;
		m_SpotLight.Direction = m_CameraController->GetCameraFront();

		SetDirLight(m_DirLight, *m_Shader);
		SetPointLights(m_PointLights, *m_Shader);
		SetSpotLight(m_SpotLight, *m_Shader);

		for (int i = 0; i < m_CubePositions.size(); i++)
		{
			auto& cubePosition = m_CubePositions[i];

			auto model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			m_Shader->SetMat4("u_ModelMatrix", model);
			OpenGLCore::Graphics::RendererAPI::DrawArrays(
				OpenGLCore::Graphics::PrimitiveType::Triangles,
				0,
				36);
		}
	}
}
