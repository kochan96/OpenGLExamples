#include "OpenGLExamplesApplication.h"

namespace OpenGLExamples
{
	OpenGLExamplesApplication::OpenGLExamplesApplication()
		:Application()
	{
	}

	void OpenGLExamplesApplication::ChangeTest(const std::string& newTestName)
	{
		auto it = std::find_if(m_ExamplePairs.begin(), m_ExamplePairs.end(), [&newTestName](const ExamplePair& pair) {return pair.Name == newTestName; });
		if (it == m_ExamplePairs.end())
		{
			LOG_CLIENT_ERROR("Could not find test {}", newTestName);
		}
		else
		{
			if (m_CurrentExample)
				delete m_CurrentExample;

			m_CurrentExample = it->CreteFunc();
		}
	}

	void OpenGLExamplesApplication::OnEvent(OpenGLCore::Events::Event& e)
	{
		if (m_CurrentExample)
			m_CurrentExample->OnEvent(e);
	}

	void OpenGLExamplesApplication::OnUpdate(OpenGLCore::Timestep ts)
	{
		if (m_CurrentExample)
			m_CurrentExample->OnUpdate(ts);
	}

	bool OpenGLExamplesApplication::Init()
	{
		if (!Application::Init())
			return false;

		//TODO: Init ImGui

		AddTest<HelloTriangleExample>("Hello Triangle");
		AddTest<ClearColorExample>("Clear Color");
		AddTest<IndexRenderingExample>("Index Rendering");

		ChangeTest("Index Rendering");

		return true;
	}
}

