#pragma once
#include "Examples/Example.h"

#include <OpenGLCore/Graphics/Shader.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <glm/glm.hpp>


namespace OpenGLExamples
{
	class TextureRenderingExample : public Example
	{
	public:
		TextureRenderingExample() = default;
		~TextureRenderingExample() override;

	protected:
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;
		virtual void Init() override;

	private:
		std::unique_ptr<OpenGLCore::Graphics::Shader> m_Shader;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;

		glm::vec3 m_ClearColor = { 0.0f,0.0f,0.0f };

		unsigned int m_TextureId = 0;
	};
}