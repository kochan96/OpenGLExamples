#pragma once
#include <iostream>
namespace OpenGLCore
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

//TODO: maybe better abbreviation than OGLC (OpenGLCore)

#define OGLC_MOUSE_BUTTON_0      ::OpenGLCore::Mouse::Button0
#define OGLC_MOUSE_BUTTON_1      ::OpenGLCore::Mouse::Button1
#define OGLC_MOUSE_BUTTON_2      ::OpenGLCore::Mouse::Button2
#define OGLC_MOUSE_BUTTON_3      ::OpenGLCore::Mouse::Button3
#define OGLC_MOUSE_BUTTON_4      ::OpenGLCore::Mouse::Button4
#define OGLC_MOUSE_BUTTON_5      ::OpenGLCore::Mouse::Button5
#define OGLC_MOUSE_BUTTON_6      ::OpenGLCore::Mouse::Button6
#define OGLC_MOUSE_BUTTON_7      ::OpenGLCore::Mouse::Button7
#define OGLC_MOUSE_BUTTON_LAST   ::OpenGLCore::Mouse::ButtonLast
#define OGLC_MOUSE_BUTTON_LEFT   ::OpenGLCore::Mouse::ButtonLeft
#define OGLC_MOUSE_BUTTON_RIGHT  ::OpenGLCore::Mouse::ButtonRight
#define OGLC_MOUSE_BUTTON_MIDDLE ::OpenGLCore::Mouse::ButtonMiddle
