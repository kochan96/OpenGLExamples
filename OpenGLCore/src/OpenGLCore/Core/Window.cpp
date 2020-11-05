#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLCore/Events/ApplicationEvent.h"
#include "OpenGLCore/Events/KeyEvent.h"
#include "OpenGLCore/Events/MouseEvent.h"

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

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						Events::KeyPressedEvent event(static_cast<KeyCode>(key), 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						Events::KeyReleasedEvent event(static_cast<KeyCode>(key));
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						Events::KeyPressedEvent event(static_cast<KeyCode>(key), 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Events::KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						Events::MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						Events::MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Events::MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Events::MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

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
			//LOG_CORE_WARNING("Window not initialized");
			return;
		}

		glfwSetWindowUserPointer(m_WindowHandle, &m_WindowData);
	}
}
