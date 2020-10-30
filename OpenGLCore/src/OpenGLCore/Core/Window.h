#pragma once
#include <string>

struct GLFWwindow;

namespace OpenGLCore
{
	struct WindowInfo
	{
		unsigned int Width;
		unsigned int Height;
		std::string Title;
		bool VSync = true;
	};

	class Window
	{
	public:
		Window();
		~Window();

		bool Init(const WindowInfo& windowInfo);
		void Shutdown();

		void OnUpdate();

		bool GetVSync() const;
		void SetVSync(bool enabled);

		unsigned int GetWidth() const { return m_WindowInfo.Width; }
		unsigned int GetHeight() const { return m_WindowInfo.Height; }

		GLFWwindow* GetNative() const { return m_WindowHandle; }

	private:
		WindowInfo m_WindowInfo;
		GLFWwindow* m_WindowHandle;
	};
}