#pragma once
#include "Examples/Example.h"

#include <OpenGLCore/Graphics/Program.h>
#include <OpenGLCore/Graphics/VertexArray.h>

namespace OpenGLExamples
{
	class HelloTriangleExample : public Example
	{
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;
		virtual void Init() override;

	private:
		std::unique_ptr<OpenGLCore::Graphics::Program> m_Program;
		std::unique_ptr<OpenGLCore::Graphics::VertexArray> m_VertexArray;
	};
}