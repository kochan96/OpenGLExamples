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

		static Application& Get() { return *m_Instance; };

		Window& GetMainWindow() const { return *m_MainWindow; }

	protected:
		virtual bool OnWindowClose(Events::WindowCloseEvent& e);
		virtual bool OnWindowResize(Events::WindowResizeEvent& e);

		virtual void OnEvent(Events::Event& e) {}
		virtual void OnUpdate(Timestep ts) {};
		virtual bool Init() { return true; }
		virtual void ImGuiRender() {};

	private:
		void OnEventApp(Events::Event& e);
		bool InitApp();
		bool InitImGui();

		void ImGuiRenderApp();

	private:
		bool m_IsRunning = false;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;

		static Application* m_Instance;

		std::unique_ptr<Window> m_MainWindow;
	};
}