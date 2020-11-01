#include "ClearColorExample.h"

#include <glad/glad.h>

namespace OpenGLExamples
{
	void ClearColorExample::Init()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}

	void ClearColorExample::OnUpdate(OpenGLCore::Timestep ts)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

