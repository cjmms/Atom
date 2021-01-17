-- @file		premake5_config.lua
-- @author		Abhikalp Unakal
-- @brief		Premake Build System - Lua script to generate build projects
-- @date		2021-01-16

basepath = "./"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Atom"
	configurations { 
	"Debug", 
	"Release" 
	}
	architecture "x86_64"

project "Atom"
	language ("C++")
	cppdialect ("C++17")
	
	targetdir (basepath.."%{prj.name}/builds/%{cfg.system}/bin/"..outputdir.."/%{prj.name}")
	objdir (basepath.."%{prj.name}/builds/%{cfg.system}/bin-int/"..outputdir.."/%{prj.name}")

	pchheader ("Pch.hpp")
	pchsource ("%{prj.name}/src/Pch.cpp")

	files { 
		basepath.."%{prj.name}/**"
	}

	if os.host() == "windows" then
		kind ("ConsoleApp")
	
		includedirs {
			-- include basepath
			basepath.."%{prj.name}",
			-- src 
			basepath.."%{prj.name}/src",
			-- lib includes
            basepath.."%{prj.name}/lib",
            -- GLEW
			basepath.."%{prj.name}/lib/GLEW/include",
			-- GLFW
			basepath.."%{prj.name}/lib/GLFW/include",
			-- glm
			basepath.."%{prj.name}/lib/glm",
			-- spdlog
			basepath.."%{prj.name}/lib/spdlog/include"
		}
		libdirs {
			-- GLEW
            basepath.."%{prj.name}/lib/GLEW/lib",
            -- GLFW
            basepath.."%{prj.name}/lib/GLFW/lib-vc2019"
            
		}

		links {
			-- OpenGL
            "opengl32",
            -- GLEW
            "glew32s.lib",
            -- GLFW
            "glfw3.lib"
		}
		postbuildcommands {

		}

		buildoptions {
			-- multiprocessor compile switch enable 
			"/MP"
		}
	end

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG" 
		optimize "On"
		
	filter "files:**.c"
		compileas "C++"

