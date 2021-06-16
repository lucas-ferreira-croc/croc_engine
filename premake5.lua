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
IncludeDir["glm"] = "CrocEngine/vendor/glm"
IncludeDir["stb_image"] = "CrocEngine/vendor/stb_image"


include "CrocEngine/vendor/GLFW"
include "CrocEngine/vendor/Glad"
include "CrocEngine/vendor/imgui"


project "CrocEngine"
	location "CrocEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crocpch.h"
	pchsource "CrocEngine/src/crocpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glm}"
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

		defines{
			"CR_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "on"

		
	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"CrocEngine/src",
		"CrocEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"CrocEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "on"


		
	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "on"

		
	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "on"