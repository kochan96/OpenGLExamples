#pragma once
#include "Window.h"
#include "Timestep.h"
#include "OpenGLCore/Events/Event.h"
#include "OpenGLCore/Events/ApplicationEvent.h"

namespace OpenGLCore
{
	class Application
	{
	public:
		Application();
		virtual ~Application();


		bool Run(const WindowInfo& windowInfo);

		void Close();

		Window& GetMainWindow() { return *m_MainWindow; }

	protected:
		virtual bool OnWindowClose(Events::WindowCloseEvent& e);
		virtual bool OnWindowResize(Events::WindowResizeEvent& e);

		virtual void OnEvent(Events::Event& e);
		virtual void OnUpdate(Timestep ts) {};
		virtual bool Init();

	private:
		bool m_IsRunning = false;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;

		std::unique_ptr<Window> m_MainWindow;
	};
}