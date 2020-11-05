#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGLCore::Utility
{
	struct Transform
	{
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Scale = { 1.0f,1.0f,1.0f };


		glm::vec3 GetFront()
		{
			glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

			glm::mat3 rotationX = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat3 rotationY = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat3 rotationZ = glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			glm::mat3 rotationMatrix = rotationZ * rotationY * rotationX;

			return rotationMatrix * front;
		}

		glm::mat4 GetMatrix() const
		{
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);

			glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

			glm::mat4 sacleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);

			return translationMatrix * rotationMatrix * sacleMatrix;
		}

		glm::mat4 GetInverseMatrix() const
		{
			glm::mat4 inverseTranslationMatrix = glm::translate(glm::mat4(1.0f), -m_Position);

			glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			glm::mat4 inverseRotationMatrix = glm::transpose(rotationZ * rotationY * rotationX);

			glm::vec3 invertedScale = glm::vec3(0.0f);
			if (m_Scale.x != 0) invertedScale.x = 1 / m_Scale.x;
			if (m_Scale.y != 0) invertedScale.y = 1 / m_Scale.x;
			if (m_Scale.z != 0) invertedScale.z = 1 / m_Scale.x;

			glm::mat4 inverseScaleMatrix = glm::scale(glm::mat4(1.0f), invertedScale);

			return inverseScaleMatrix * inverseRotationMatrix * inverseTranslationMatrix;
		}
	};
}