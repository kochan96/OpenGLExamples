#pragma once
#include <iostream>

namespace OpenGLCore
{
    typedef enum class KeyCode : uint16_t
    {
        // From glfw3.h
        Space = 32,
        Apostrophe = 39, /* ' */
        Comma = 44, /* , */
        Minus = 45, /* - */
        Period = 46, /* . */
        Slash = 47, /* / */

        D0 = 48, /* 0 */
        D1 = 49, /* 1 */
        D2 = 50, /* 2 */
        D3 = 51, /* 3 */
        D4 = 52, /* 4 */
        D5 = 53, /* 5 */
        D6 = 54, /* 6 */
        D7 = 55, /* 7 */
        D8 = 56, /* 8 */
        D9 = 57, /* 9 */

        Semicolon = 59, /* ; */
        Equal = 61, /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,  /* [ */
        Backslash = 92,  /* \ */
        RightBracket = 93,  /* ] */
        GraveAccent = 96,  /* ` */

        World1 = 161, /* non-US #1 */
        World2 = 162, /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        /* Keypad */
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
}


//TODO: maybe better abbreviation than OGLC (OpenGLCore)
// From glfw3.h
#define OGLC_KEY_SPACE           ::OpenGLCore::Key::Space
#define OGLC_KEY_APOSTROPHE      ::OpenGLCore::Key::Apostrophe    /* ' */
#define OGLC_KEY_COMMA           ::OpenGLCore::Key::Comma         /* , */
#define OGLC_KEY_MINUS           ::OpenGLCore::Key::Minus         /* - */
#define OGLC_KEY_PERIOD          ::OpenGLCore::Key::Period        /* . */
#define OGLC_KEY_SLASH           ::OpenGLCore::Key::Slash         /* / */
#define OGLC_KEY_0               ::OpenGLCore::Key::D0
#define OGLC_KEY_1               ::OpenGLCore::Key::D1
#define OGLC_KEY_2               ::OpenGLCore::Key::D2
#define OGLC_KEY_3               ::OpenGLCore::Key::D3
#define OGLC_KEY_4               ::OpenGLCore::Key::D4
#define OGLC_KEY_5               ::OpenGLCore::Key::D5
#define OGLC_KEY_6               ::OpenGLCore::Key::D6
#define OGLC_KEY_7               ::OpenGLCore::Key::D7
#define OGLC_KEY_8               ::OpenGLCore::Key::D8
#define OGLC_KEY_9               ::OpenGLCore::Key::D9
#define OGLC_KEY_SEMICOLON       ::OpenGLCore::Key::Semicolon     /* ; */
#define OGLC_KEY_EQUAL           ::OpenGLCore::Key::Equal         /* = */
#define OGLC_KEY_A               ::OpenGLCore::Key::A
#define OGLC_KEY_B               ::OpenGLCore::Key::B
#define OGLC_KEY_C               ::OpenGLCore::Key::C
#define OGLC_KEY_D               ::OpenGLCore::Key::D
#define OGLC_KEY_E               ::OpenGLCore::Key::E
#define OGLC_KEY_F               ::OpenGLCore::Key::F
#define OGLC_KEY_G               ::OpenGLCore::Key::G
#define OGLC_KEY_H               ::OpenGLCore::Key::H
#define OGLC_KEY_I               ::OpenGLCore::Key::I
#define OGLC_KEY_J               ::OpenGLCore::Key::J
#define OGLC_KEY_K               ::OpenGLCore::Key::K
#define OGLC_KEY_L               ::OpenGLCore::Key::L
#define OGLC_KEY_M               ::OpenGLCore::Key::M
#define OGLC_KEY_N               ::OpenGLCore::Key::N
#define OGLC_KEY_O               ::OpenGLCore::Key::O
#define OGLC_KEY_P               ::OpenGLCore::Key::P
#define OGLC_KEY_Q               ::OpenGLCore::Key::Q
#define OGLC_KEY_R               ::OpenGLCore::Key::R
#define OGLC_KEY_S               ::OpenGLCore::Key::S
#define OGLC_KEY_T               ::OpenGLCore::Key::T
#define OGLC_KEY_U               ::OpenGLCore::Key::U
#define OGLC_KEY_V               ::OpenGLCore::Key::V
#define OGLC_KEY_W               ::OpenGLCore::Key::W
#define OGLC_KEY_X               ::OpenGLCore::Key::X
#define OGLC_KEY_Y               ::OpenGLCore::Key::Y
#define OGLC_KEY_Z               ::OpenGLCore::Key::Z
#define OGLC_KEY_LEFT_BRACKET    ::OpenGLCore::Key::LeftBracket   /* [ */
#define OGLC_KEY_BACKSLASH       ::OpenGLCore::Key::Backslash     /* \ */
#define OGLC_KEY_RIGHT_BRACKET   ::OpenGLCore::Key::RightBracket  /* ] */
#define OGLC_KEY_GRAVE_ACCENT    ::OpenGLCore::Key::GraveAccent   /* ` */
#define OGLC_KEY_WORLD_1         ::OpenGLCore::Key::World1        /* non-US #1 */
#define OGLC_KEY_WORLD_2         ::OpenGLCore::Key::World2        /* non-US #2 */

/* Function keys */
#define OGLC_KEY_ESCAPE          ::OpenGLCore::Key::Escape
#define OGLC_KEY_ENTER           ::OpenGLCore::Key::Enter
#define OGLC_KEY_TAB             ::OpenGLCore::Key::Tab
#define OGLC_KEY_BACKSPACE       ::OpenGLCore::Key::Backspace
#define OGLC_KEY_INSERT          ::OpenGLCore::Key::Insert
#define OGLC_KEY_DELETE          ::OpenGLCore::Key::Delete
#define OGLC_KEY_RIGHT           ::OpenGLCore::Key::Right
#define OGLC_KEY_LEFT            ::OpenGLCore::Key::Left
#define OGLC_KEY_DOWN            ::OpenGLCore::Key::Down
#define OGLC_KEY_UP              ::OpenGLCore::Key::Up
#define OGLC_KEY_PAGE_UP         ::OpenGLCore::Key::PageUp
#define OGLC_KEY_PAGE_DOWN       ::OpenGLCore::Key::PageDown
#define OGLC_KEY_HOME            ::OpenGLCore::Key::Home
#define OGLC_KEY_END             ::OpenGLCore::Key::End
#define OGLC_KEY_CAPS_LOCK       ::OpenGLCore::Key::CapsLock
#define OGLC_KEY_SCROLL_LOCK     ::OpenGLCore::Key::ScrollLock
#define OGLC_KEY_NUM_LOCK        ::OpenGLCore::Key::NumLock
#define OGLC_KEY_PRINT_SCREEN    ::OpenGLCore::Key::PrintScreen
#define OGLC_KEY_PAUSE           ::OpenGLCore::Key::Pause
#define OGLC_KEY_F1              ::OpenGLCore::Key::F1
#define OGLC_KEY_F2              ::OpenGLCore::Key::F2
#define OGLC_KEY_F3              ::OpenGLCore::Key::F3
#define OGLC_KEY_F4              ::OpenGLCore::Key::F4
#define OGLC_KEY_F5              ::OpenGLCore::Key::F5
#define OGLC_KEY_F6              ::OpenGLCore::Key::F6
#define OGLC_KEY_F7              ::OpenGLCore::Key::F7
#define OGLC_KEY_F8              ::OpenGLCore::Key::F8
#define OGLC_KEY_F9              ::OpenGLCore::Key::F9
#define OGLC_KEY_F10             ::OpenGLCore::Key::F10
#define OGLC_KEY_F11             ::OpenGLCore::Key::F11
#define OGLC_KEY_F12             ::OpenGLCore::Key::F12
#define OGLC_KEY_F13             ::OpenGLCore::Key::F13
#define OGLC_KEY_F14             ::OpenGLCore::Key::F14
#define OGLC_KEY_F15             ::OpenGLCore::Key::F15
#define OGLC_KEY_F16             ::OpenGLCore::Key::F16
#define OGLC_KEY_F17             ::OpenGLCore::Key::F17
#define OGLC_KEY_F18             ::OpenGLCore::Key::F18
#define OGLC_KEY_F19             ::OpenGLCore::Key::F19
#define OGLC_KEY_F20             ::OpenGLCore::Key::F20
#define OGLC_KEY_F21             ::OpenGLCore::Key::F21
#define OGLC_KEY_F22             ::OpenGLCore::Key::F22
#define OGLC_KEY_F23             ::OpenGLCore::Key::F23
#define OGLC_KEY_F24             ::OpenGLCore::Key::F24
#define OGLC_KEY_F25             ::OpenGLCore::Key::F25

/* Keypad */
#define OGLC_KEY_KP_0            ::OpenGLCore::Key::KP0
#define OGLC_KEY_KP_1            ::OpenGLCore::Key::KP1
#define OGLC_KEY_KP_2            ::OpenGLCore::Key::KP2
#define OGLC_KEY_KP_3            ::OpenGLCore::Key::KP3
#define OGLC_KEY_KP_4            ::OpenGLCore::Key::KP4
#define OGLC_KEY_KP_5            ::OpenGLCore::Key::KP5
#define OGLC_KEY_KP_6            ::OpenGLCore::Key::KP6
#define OGLC_KEY_KP_7            ::OpenGLCore::Key::KP7
#define OGLC_KEY_KP_8            ::OpenGLCore::Key::KP8
#define OGLC_KEY_KP_9            ::OpenGLCore::Key::KP9
#define OGLC_KEY_KP_DECIMAL      ::OpenGLCore::Key::KPDecimal
#define OGLC_KEY_KP_DIVIDE       ::OpenGLCore::Key::KPDivide
#define OGLC_KEY_KP_MULTIPLY     ::OpenGLCore::Key::KPMultiply
#define OGLC_KEY_KP_SUBTRACT     ::OpenGLCore::Key::KPSubtract
#define OGLC_KEY_KP_ADD          ::OpenGLCore::Key::KPAdd
#define OGLC_KEY_KP_ENTER        ::OpenGLCore::Key::KPEnter
#define OGLC_KEY_KP_EQUAL        ::OpenGLCore::Key::KPEqual

#define OGLC_KEY_LEFT_SHIFT      ::OpenGLCore::Key::LeftShift
#define OGLC_KEY_LEFT_CONTROL    ::OpenGLCore::Key::LeftControl
#define OGLC_KEY_LEFT_ALT        ::OpenGLCore::Key::LeftAlt
#define OGLC_KEY_LEFT_SUPER      ::OpenGLCore::Key::LeftSuper
#define OGLC_KEY_RIGHT_SHIFT     ::OpenGLCore::Key::RightShift
#define OGLC_KEY_RIGHT_CONTROL   ::OpenGLCore::Key::RightControl
#define OGLC_KEY_RIGHT_ALT       ::OpenGLCore::Key::RightAlt
#define OGLC_KEY_RIGHT_SUPER     ::OpenGLCore::Key::RightSuper
#define OGLC_KEY_MENU            ::OpenGLCore::Key::Menu
