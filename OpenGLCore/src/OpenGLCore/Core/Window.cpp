#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OpenGLCore
{
	static uint8_t windowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		//LOG
	}

	Window::Window()
	{
		m_WindowHandle = nullptr;
	}

	Window::~Window()
	{
		Shutdown();
	}

	bool Window::Init(const WindowInfo& windowInfo)
	{
		m_WindowInfo = windowInfo;

		if (windowCount == 0)
		{
			if (!glfwInit())
			{
				//TODO LOG
				return false;
			}

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); //TODO: conditional enable

		m_WindowHandle = glfwCreateWindow(
			m_WindowInfo.Width,
			m_WindowInfo.Height,
			m_WindowInfo.Title.c_str(),
			NULL,
			NULL);

		windowCount++;

		if (!m_WindowHandle)
		{
			//TODO: LOG
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGL())
		{
			//TODO: LOG
			Shutdown();
			return false;
		}

		SetVSync(m_WindowInfo.VSync);

		return true;
	}

	void Window::Shutdown()
	{
		if (!m_WindowHandle)
		{
			windowCount--;
			glfwDestroyWindow(m_WindowHandle);
			if (windowCount == 0)
			{
				glfwTerminate();
			}
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandle);
	}

	bool Window::GetVSync() const
	{
		return m_WindowInfo.VSync;
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_WindowInfo.VSync = enabled;
	}
}
