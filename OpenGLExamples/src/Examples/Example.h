#pragma once
#include <OpenGLCore/Events/Event.h>
#include <OpenGLCore/Core/Timestep.h>

namespace OpenGLExamples
{
	class Example
	{
	public:
		Example() {};
		virtual ~Example() {};

		virtual void Init() { };
		virtual void OnEvent(OpenGLCore::Events::Event& e) {};
		virtual void OnUpdate(OpenGLCore::Timestep ts) {};
	};
}