workspace "MyHazel"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
		"Release",
		"Dist"
	}

	startproject "Hazelnut"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MyHazel/vendor/GLFW/include"
IncludeDir["Glad"] = "MyHazel/vendor/Glad/include"
IncludeDir["ImGui"] = "MyHazel/vendor/ImGui"
IncludeDir["glm"] = "MyHazel/vendor/glm"

include "MyHazel/vendor/GLFW"
include "MyHazel/vendor/Glad"
include "MyHazel/vendor/ImGui"

project "MyHazel"
	location "MyHazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "MyHazel/src/hzpch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{prj.name}/vendor/assimp/include",
		"%{prj.name}/vendor/stb/include"
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
		
		defines 
		{ 
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
				
	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"

project "Hazelnut"
	location "Hazelnut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links 
	{ 
		"MyHazel"
	}
	
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}
	
	includedirs 
	{
		"%{prj.name}/src",
		"MyHazel/src",
		"MyHazel/vendor",
		"%{IncludeDir.glm}"
	}

	postbuildcommands 
	{
		'{COPY} "../Hazelnut/assets" "%{cfg.targetdir}/assets"'
	}
	
	filter "system:windows"
		systemversion "latest"
				
		defines 
		{ 
			"HZ_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "on"

		links
		{
			"MyHazel/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../MyHazel/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
		}
				
	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "on"

		links
		{
			"MyHazel/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../MyHazel/vendor/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "on"

		links
		{
			"MyHazel/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../MyHazel/vendor/assimp/bin/Release/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
		}
		
--[[project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links 
	{ 
		"MyHazel"
	}
	
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}
	
	includedirs 
	{
		"%{prj.name}/src",
		"MyHazel/src",
		"MyHazel/vendor",
		"%{IncludeDir.glm}"
	}
	
	filter "system:windows"
		systemversion "latest"
				
		defines 
		{ 
			"HZ_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "on"

		links
		{
			"MyHazel/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		}
				
	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "on"

		links
		{
			"MyHazel/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
		}

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "on"

		links
		{
			"MyHazel/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
		}
--]]