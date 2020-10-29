workspace "OpenGLExamples"
    architecture "x64"    

    configurations 
    { 
        "Debug",
        "Release"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
dependenciesDir = "dependencies/"
mainDir = "OpenGLExamples/"

IncludeDir = {}
IncludeDir["GLAD"] = (mainDir .. dependenciesDir .. "glad/include")
IncludeDir["GLFW"] = (mainDir .. dependenciesDir .. "glfw/include") 

group "Dependencies"
    include (mainDir .. dependenciesDir .. "glad")
    include (mainDir .. dependenciesDir .. "glfw")
group ""

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
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"