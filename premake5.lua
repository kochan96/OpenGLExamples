workspace "OpenGLExamples"
    architecture "x64"    

    configurations 
    { 
        "Debug",
        "Release"
    }

group "Dependencies"
    include "OpenGLCore/dependencies/glad/"
    include "OpenGLCore/dependencies/glfw/"
    include "OpenGLCore/dependencies/imgui/"
    
group "Core"
    include "OpenGLCore/"
group ""

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

OpenGLExamplesIncludeDir = {}
OpenGLExamplesIncludeDir["OpenGLCore"] = "OpenGLCore/src/"
OpenGLExamplesIncludeDir["IMGUI"] = "OpenGLCore/dependencies/imgui/"
OpenGLExamplesIncludeDir["GLAD"] = "OpenGLCore/dependencies/glad/include/"
OpenGLExamplesIncludeDir["SPDLOG"] = "OpenGLCore/dependencies/spdlog/include/"
OpenGLExamplesIncludeDir["GLM"] = "OpenGLCore/dependencies/glm/"


project "OpenGLExamples"
    location "OpenGLExamples"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/assets/**"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{OpenGLExamplesIncludeDir.OpenGLCore}",
        "%{OpenGLExamplesIncludeDir.GLAD}",
        "%{OpenGLExamplesIncludeDir.IMGUI}",
        "%{OpenGLExamplesIncludeDir.GLM}",
        "%{OpenGLExamplesIncludeDir.SPDLOG}",
    }

    links
    {
        "OpenGLCore",
        "ImGui"
    }

    postbuildcommands 
	{
        '{COPY} "../OpenGLExamples/assets" "%{cfg.targetdir}/assets"',
	}

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"