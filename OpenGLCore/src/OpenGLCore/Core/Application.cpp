#include "Application.h"
#include "Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace OpenGLCore
{
	Application::Application()
	{
		m_MainWindow = std::make_unique<Window>();
	}

	Application::~Application()
	{
	}

	bool Application::InitApp()
	{
		Logger::Init();

		return Init();
	}

	void Application::Close()
	{
		m_IsRunning = false;
	}

	bool Application::Run(const WindowInfo& windowInfo)
	{
		if (!m_MainWindow->Init(windowInfo))
			return false;

		m_MainWindow->SetEventCallback(std::bind(&Application::OnEventApp, this, std::placeholders::_1));

		if (!InitApp())
			return false;

		m_IsRunning = true;

		while (m_IsRunning)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				OnUpdate(timestep);
			}

			m_MainWindow->OnUpdate();
		}

		return true;
	}

	void Application::OnEventApp(Events::Event& e)
	{
		Events::EventDispatcher eventDispatcher(e);

		eventDispatcher.Dispatch<Events::WindowCloseEvent>(
			std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		eventDispatcher.Dispatch<Events::WindowResizeEvent>(
			std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		if (!e.Handled)
			OnEvent(e);
	}

	bool Application::OnWindowResize(Events::WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}



	bool Application::OnWindowClose(Events::WindowCloseEvent& e)
	{
		Close();
		return true;
	}
}
