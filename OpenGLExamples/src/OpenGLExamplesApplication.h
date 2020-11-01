#pragma once
#include <OpenGLCore/Core/Application.h>
#include "Examples/Examples.h"

namespace OpenGLExamples
{
	class OpenGLExamplesApplication : public OpenGLCore::Application
	{
	public:
		OpenGLExamplesApplication();

		

	protected:
		virtual void OnEvent(OpenGLCore::Events::Event& e) override;
		virtual void OnUpdate(OpenGLCore::Timestep ts) override;
		virtual bool Init() override;

	private:
		template <typename T>
		void AddTest(const std::string& name);
		
		void ChangeTest(const std::string& newTestName);

	private:
		struct ExamplePair
		{
			std::string Name;
			std::function<Example* ()> CreteFunc;
		};

		Example* m_CurrentExample = nullptr;

		std::vector<ExamplePair> m_ExamplePairs; //TODO maybe use somekind of dictionary instead of vector
	};

	template <typename T>
	inline void OpenGLExamplesApplication::AddTest(const std::string& name)
	{
		ExamplePair pair;
		pair.Name = name;
		pair.CreteFunc = []() {
			Example* example = new T();
			example->Init();
			return example;
		};

		if (m_ExamplePairs.empty())
		{
			m_CurrentExample = pair.CreteFunc();
		}

		m_ExamplePairs.push_back(pair);
	}
}