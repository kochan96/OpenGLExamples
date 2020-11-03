#pragma once
#include "Examples/Example.h"

#include <memory>
#include <OpenGLCore/Graphics/Shader.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <OpenGLCore/Graphics/Texture2D.h>

#include <glm/glm.hpp>


namespace OpenGLExamples
{
	class TextureRenderingExample : public Example
	{
	protected:
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;
		virtual void Init() override;

	private:
		std::unique_ptr<OpenGLCore::Graphics::Shader> m_Shader;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;
		std::unique_ptr<OpenGLCore::Graphics::Texture2D> m_Texture;

		glm::vec3 m_ClearColor = { 0.0f,0.0f,0.0f };

	};
}