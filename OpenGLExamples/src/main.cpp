#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <OpenGLCore/Core/Window.h>
#include <OpenGLCore/Graphics/Buffer.h>
#include <OpenGLCore/Graphics/VertexArray.h>
#include <OpenGLCore/Graphics/Program.h>
#include <OpenGLCore/Events/ApplicationEvent.h>
#include <functional>

bool running = false;

bool OnClose(OpenGLCore::Events::WindowCloseEvent& closeEvent)
{
	running = false;
	return true;
}

bool OnResize(OpenGLCore::Events::WindowResizeEvent& resizeEvent)
{
	glViewport(0, 0, resizeEvent.GetWidth(), resizeEvent.GetHeight());
	return true;
}

void OnUpdate(OpenGLCore::Events::Event& event)
{
	OpenGLCore::Events::EventDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<OpenGLCore::Events::WindowResizeEvent>(std::bind(&OnResize, std::placeholders::_1));
	eventDispatcher.Dispatch<OpenGLCore::Events::WindowCloseEvent>(std::bind(&OnClose, std::placeholders::_1));
}

int main()
{

	OpenGLCore::WindowInfo windowInfo;
	windowInfo.Width = 1024;
	windowInfo.Height = 768;
	windowInfo.Title = "Hello World";

	OpenGLCore::Window window;
	if (!window.Init(windowInfo))
	{
		return EXIT_FAILURE;
	}

	window.SetEventCallback(OnUpdate);

	float vertices[] = {
		-1.0f,-1.0f,
		1.0f,-1.0f,
		0.0f,1.0f
	};

	OpenGLCore::Graphics::Shader vertexShader("assets/simpleShader.vert", OpenGLCore::Graphics::ShaderType::Vertex);
	OpenGLCore::Graphics::Shader fragmentShader("assets/simpleShader.frag", OpenGLCore::Graphics::ShaderType::Fragment);

	OpenGLCore::Graphics::Program program;
	program.Create({ vertexShader,fragmentShader });

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	OpenGLCore::Graphics::VertexArray vertexArray;
	auto vertexBuffer = std::make_shared<OpenGLCore::Graphics::VertexBuffer>(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{OpenGLCore::Graphics::ShaderDataType::Float2,"a_Position"}
		});

	vertexArray.AddVertexBuffer(vertexBuffer);

	program.Use();
	vertexArray.Bind();

	running = true;

	while (running)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.OnUpdate();
	}

	window.Shutdown();
	return EXIT_SUCCESS;
}