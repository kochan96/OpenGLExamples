#pragma once
#include <string>
#include <functional>
#include "OpenGLCore/Events/Event.h"

struct GLFWwindow;

namespace OpenGLCore
{
	struct WindowInfo
	{
		unsigned int Width = 640;
		unsigned int Height = 480;
		std::string Title = "Main Window";
		bool VSync = true;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Events::Event&)>;

		Window();
		~Window();

		bool Init(const WindowInfo& windowInfo);
		void Shutdown();

		void OnUpdate();

		void SetEventCallback(const EventCallbackFn& callback)
		{
			m_WindowData.EventCallback = callback;
			InitCallbacks();
		}

		bool GetVSync() const;
		void SetVSync(bool enabled);

		unsigned int GetWidth() const { return m_WindowData.WindowInfo.Width; }
		unsigned int GetHeight() const { return m_WindowData.WindowInfo.Width; }

	private:
		void InitCallbacks();

		struct WindowData
		{
			WindowInfo WindowInfo;

			EventCallbackFn EventCallback;
		};

		WindowData m_WindowData;
		GLFWwindow* m_WindowHandle;
	};
}