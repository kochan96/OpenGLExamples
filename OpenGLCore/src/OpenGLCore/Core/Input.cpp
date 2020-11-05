#include "Input.h"
#include "MouseCode.h"
#include "OpenGLCore/Core/Application.h"

#include <GLFW/glfw3.h>

namespace OpenGLCore
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		auto& window = Application::Get().GetMainWindow();
		auto state = glfwGetKey(window.GetWindowHandle(), static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto& window =Application::Get().GetMainWindow();
		auto state = glfwGetMouseButton(window.GetWindowHandle(), static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto& window = Application::Get().GetMainWindow();
		double xpos, ypos;
		glfwGetCursorPos(window.GetWindowHandle(), &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto mousePosition = GetMousePosition();
		return mousePosition.x;
	}

	float Input::GetMouseY()
	{
		auto mousePosition = GetMousePosition();
		return mousePosition.y;
	}
}
