#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <OpenGLCore/Core/Window.h>
#include <OpenGLCore/Graphics/Buffer.h>
#include <OpenGLCore/Graphics/VertexArray.h>
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

	const char* vertexShaderSource = "#version 440 core\n"
		"layout (location = 0) in vec2 a_Position;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(a_Position.x, a_Position.y, 0.0f, 1.0);\n"
		"}\0";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* fragmentShaderSource = "#version 440 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::LINKING_ERROR\n" << infoLog << std::endl;
	}

	glViewport(0, 0, windowInfo.Width, windowInfo.Height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	OpenGLCore::VertexArray vertexArray;
	auto vertexBuffer = std::make_shared<OpenGLCore::VertexBuffer>(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{OpenGLCore::ShaderDataType::Float2,"a_Position"}
		});

	vertexArray.AddVertexBuffer(vertexBuffer);

	glUseProgram(shaderProgram);
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