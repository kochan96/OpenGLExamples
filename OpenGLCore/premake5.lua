
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OpenGLCoreIncludeDir = {}
OpenGLCoreIncludeDir["GLAD"] = "dependencies/glad/include"
OpenGLCoreIncludeDir["GLFW"] = "dependencies/glfw/include"
OpenGLCoreIncludeDir["IMGUI"] = "dependencies/imgui/"
OpenGLCoreIncludeDir["SPDLOG"] = "dependencies/spdlog/include"
OpenGLCoreIncludeDir["STB_IMAGE"] = "dependencies/stb_image/"
OpenGLCoreIncludeDir["GLM"] = "dependencies/glm/"

project "OpenGLCore"
    kind "StaticLib"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    targetdir ("bin/" .. outputDir .. "%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files 
    {
        "src/**.cpp",
        "src/**.h",
    }

    defines
	{
		"GLFW_INCLUDE_NONE"
	}

    includedirs
    {
        "src/",
        "%{OpenGLCoreIncludeDir.GLAD}",
        "%{OpenGLCoreIncludeDir.GLFW}",
        "%{OpenGLCoreIncludeDir.IMGUI}",
        "%{OpenGLCoreIncludeDir.GLM}",
        "%{OpenGLCoreIncludeDir.SPDLOG}",
        "%{OpenGLCoreIncludeDir.STB_IMAGE}"
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"