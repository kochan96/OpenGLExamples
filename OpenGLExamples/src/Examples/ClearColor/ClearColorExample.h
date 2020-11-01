#pragma once
#include "Examples/Example.h"
#include <OpenGLCore/Core/Timestep.h>

namespace OpenGLExamples
{
	class ClearColorExample : public Example
	{
	public:
		virtual void Init() override;
		virtual void OnUpdate(OpenGLCore::Timestep ts);
	};
}