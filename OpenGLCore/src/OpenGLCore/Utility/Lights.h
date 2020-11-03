#pragma once
#include <glm/glm.hpp>

namespace OpenGLCore::Utility
{
	struct PointLight
	{
		glm::vec3 Positon = { 0.0f,0.0f,0.0f };

		glm::vec3 Ambient = { 0.05f,0.05f,0.05f };
		glm::vec3 Diffuse = { 0.8f,0.8f,0.8f };
		glm::vec3 Specular = { 1.0f,1.0f,1.0f };

		bool EnableAttenuation = true;
		float Constant = 1.0f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;
	};

	struct DirLight
	{
		glm::vec3 Direction = { -0.2f, -1.0f, -0.3f };

		glm::vec3 Ambient = { 0.05f,0.05f,0.05f };
		glm::vec3 Diffuse = { 0.4f,0.4f,0.4f };
		glm::vec3 Specular = { 1.0f,1.0f,1.0f };
	};

	struct SpotLight
	{
		glm::vec3 Position = { 0.0f,0.0f,0.0f };

		glm::vec3 Direction = { 0.0f,0.0f, -1.0f }; //front
		glm::vec3 Ambient = { 0.0f,0.0f,0.0f };
		glm::vec3 Diffuse = { 1.0f,1.0f,1.0f };
		glm::vec3 Specular = { 1.0f,1.0f,1.0f };

		float cutOff = glm::cos(glm::radians(12.5f));
		float outerCutOff = glm::cos(glm::radians(15.0f));

		bool EnableAttenuation = true;
		float Constant = 1.0f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;
	};


}