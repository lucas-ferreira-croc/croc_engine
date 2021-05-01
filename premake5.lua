workspace "CrocEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CrocEngine"
	location "CrocEngine"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"CROC_PLATAFORM_WINDOWS",
			"CR_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	

	filter "configurations:Debug"
		defines "CR_DEBUG"
		symbols "On"


		
	filter "configurations:Release"
		defines "CR_RELEASE"
		optimize "On"

		
	filter "configurations:Dist"
		defines "CR_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	
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
		staticruntime "On"
		systemversion "latest"

		defines{
			"CROC_PLATAFORM_WINDOWS",
		}
	

	filter "configurations:Debug"
		defines "CR_DEBUG"
		symbols "On"


		
	filter "configurations:Release"
		defines "CR_RELEASE"
		optimize "On"

		
	filter "configurations:Dist"
		defines "CR_DIST"
		optimize "On"