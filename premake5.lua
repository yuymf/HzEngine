include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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
