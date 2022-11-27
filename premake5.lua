include "./vendor/premake/premake_customization/solution_items.lua"

workspace "MyHazel"
	architecture "x86_64"
	startproject "Hazelnut"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include directories relatave to root folders
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/MyHazel/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/MyHazel/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/MyHazel/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/MyHazel/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/MyHazel/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/MyHazel/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/MyHazel/vendor/yaml-cpp/include"

group "Dependencies"
	include "vendor/premake"
	include "MyHazel/vendor/GLFW"
	include "MyHazel/vendor/Glad"
	include "MyHazel/vendor/imgui"
	include "MyHazel/vendor/yaml-cpp"
group ""

include "MyHazel"
include "Sandbox"
include "Hazelnut"
