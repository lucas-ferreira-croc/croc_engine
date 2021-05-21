workspace "CrocEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "CrocEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "CrocEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "CrocEngine/vendor/imgui"


include "CrocEngine/vendor/GLFW"
include "CrocEngine/vendor/Glad"
include "CrocEngine/vendor/ImGui"


project "CrocEngine"
	location "CrocEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crocpch.h"
	pchsource "CrocEngine/src/crocpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"CROC_PLATAFORM_WINDOWS",
			"CR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
	

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "On"


		
	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "On"

		
	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
	
		"CrocEngine/vendor/spdlog/include",
		"CrocEngine/src"
	}

	links
	{
		"CrocEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"CROC_PLATAFORM_WINDOWS",
		}
	

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "On"


		
	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "On"

		
	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "On"