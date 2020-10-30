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
    
group "Core"
    include "OpenGLCore/"
group ""

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["OpenGLCore"] = "OpenGLCore/src/"
IncludeDir["GLAD"] = "OpenGLCore/dependencies/glad/include/"
IncludeDir["GLFW"] = "OpenGLCore/dependencies/glfw/include/"


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
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.OpenGLCore}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLFW}",
    }

    links
    {
        "OpenGLCore",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"