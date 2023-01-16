workspace "ChessClone"
	architecture "x86"

	configurations {
		"Debug",
		"Release"
	}

outputdir ="%{cfg.architecture}-%{cfg.buildcfg}"

project "ChessClone"
	location "ChessClone"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/res/**.shader"
	}

	includedirs
	{
		"Depedencies/GLFW/include/GLFW",
		"Depedencies/GLEW/include/GL"
	}

	libdirs
	{
		"Depedencies/GLEW/Librairies/Release/Win32",
		"Depedencies/GLFW/lib-vc2022"
	}

	links{"glew32s","glfw3","opengl32"}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"GLEW_STATIC" 
		}

	filter "configurations:Debug"
		symbols "On"
	filter "configurations:Release"
		optimize "On"

