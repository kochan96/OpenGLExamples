#include "Application.h"
#include "Logger.h"
#include "OpenGLCore/Graphics/RendererAPI.h"

#include <GLFW/glfw3.h>

#include <imgui.h>

#define IMGUI_IMPL_API
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

namespace OpenGLCore
{
	Application* Application::m_Instance;

	Application::Application()
	{
		if (m_Instance)
		{
			LOG_CORE_CRITICAL("Should be only one instance of Aplication");
		}

		m_Instance = this;
		m_MainWindow = std::make_unique<Window>();
	}

	Application::~Application()
	{
		Close();
	}

	bool Application::InitApp()
	{
		Logger::Init();
		if (!Graphics::RendererAPI::Init())
			return false;

		if (!InitImGui())
			return false;

		return Init();
	}

	bool Application::InitImGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		ImGui::StyleColorsClassic();

		if (!ImGui_ImplOpenGL3_Init("#version 440"))
		{
			LOG_CORE_ERROR("Could not initialize imgui for opengl");
			return false;
		}

		if (!ImGui_ImplGlfw_InitForOpenGL(m_MainWindow->GetWindowHandle(), true))
		{
			LOG_CORE_ERROR("Could not initialize imgui for glfw");
			ImGui_ImplGlfw_Shutdown();
			return false;
		}

		return true;
	}

	void Application::ImGuiRenderApp()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiRender();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Application::Close()
	{
		m_IsRunning = false;
	}

	bool Application::Run(const WindowInfo& windowInfo)
	{
		m_MainWindow->SetEventCallback(std::bind(&Application::OnEventApp, this, std::placeholders::_1));

		if (!m_MainWindow->Init(windowInfo))
			return false;


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

			ImGuiRenderApp();

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
		Graphics::RendererAPI::SetViewPort(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnWindowClose(Events::WindowCloseEvent& e)
	{
		Close();
		return true;
	}
}
