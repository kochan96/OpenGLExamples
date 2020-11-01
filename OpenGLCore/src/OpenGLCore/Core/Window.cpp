#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLCore/Events/ApplicationEvent.h"

#include "Logger.h"

namespace OpenGLCore
{
	static uint8_t windowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_CORE_ERROR("GLFW Error {}: {}", error, description);
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
		if (windowCount == 0)
		{
			if (!glfwInit())
			{
				LOG_CORE_ERROR("Could not initialize glfw");
				return false;
			}

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); //TODO: conditional enable

		m_WindowHandle = glfwCreateWindow(
			windowInfo.Width,
			windowInfo.Height,
			windowInfo.Title.c_str(),
			NULL,
			NULL);

		windowCount++;

		if (!m_WindowHandle)
		{
			LOG_CORE_ERROR("Could not create window");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGL())
		{
			LOG_CORE_ERROR("Could not load glad");
			Shutdown();
			return false;
		}

		SetVSync(windowInfo.VSync);

		m_WindowData.WindowInfo = windowInfo;

		glfwSetWindowUserPointer(m_WindowHandle, &m_WindowData);

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.WindowInfo.Width = width;
				data.WindowInfo.Height = height;

				Events::WindowResizeEvent event(width, height);

				if (data.EventCallback)
					data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				Events::WindowCloseEvent event;
				if (data.EventCallback)
					data.EventCallback(event);
			});

		//TODO: Key and mouse events

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
		return m_WindowData.WindowInfo.VSync;
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_WindowData.WindowInfo.VSync = enabled;
	}

	void Window::InitCallbacks()
	{
		if (!m_WindowHandle)
		{
			LOG_CORE_ERROR("Window not initialized");
			return;
		}

		glfwSetWindowUserPointer(m_WindowHandle, &m_WindowData);
	}
}
