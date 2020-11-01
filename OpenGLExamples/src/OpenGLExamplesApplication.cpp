#include "OpenGLExamplesApplication.h"
#include "imgui.h"

namespace OpenGLExamples
{
	OpenGLExamplesApplication::OpenGLExamplesApplication()
		:Application()
	{
	}

	void OpenGLExamplesApplication::ChangeExample(const std::string& newTestName)
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
		AddTest<IndexRenderingExample>("Index Rendering");

		return true;
	}

	void OpenGLExamplesApplication::ImGuiRender()
	{
		if (ImGui::Begin("Examples"))
		{
			for (auto example : m_ExamplePairs)
			{
				if (ImGui::Button(example.Name.c_str()))
					ChangeExample(example.Name);
			}
		}

		ImGui::End();

		if (m_CurrentExample)
			m_CurrentExample->ImGuiRender();
	}
}

