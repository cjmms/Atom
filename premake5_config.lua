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
		kind ("WindowedApp")
	
		defines {
			"GLEW_STATIC"
		}

		includedirs {
			-- include basepath
			basepath.."%{prj.name}/",
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
			basepath.."%{prj.name}/lib/spdlog/include",
			-- fmod
			basepath.."%{prj.name}/lib/fmod/api/core/inc/",
			basepath.."%{prj.name}/lib/fmod/api/fsbank/inc/",
			basepath.."%{prj.name}/lib/fmod/api/studio/inc/",
			-- imgui
			basepath.."%{prj.name}/lib/imgui/"
		}
		libdirs {
			-- GLEW
            basepath.."%{prj.name}/lib/GLEW/lib",
            -- GLFW
			basepath.."%{prj.name}/lib/GLFW/lib-vc2019",
			-- fmod
			basepath.."%{prj.name}/lib/fmod/api/core/lib/x64/",
			basepath.."%{prj.name}/lib/fmod/api/fsbank/lib/x64/",
			basepath.."%{prj.name}/lib/fmod/api/studio/lib/x64/"    
		}

		links {
			-- OpenGL
            "opengl32",
            -- GLEW
            "glew32s.lib",
            -- GLFW
			"glfw3.lib",
			-- fmod
			"fmod_vc.lib",
			"fmodstudio_vc.lib",
			"fsbank_vc.lib"
		}
		postbuildcommands {
			-- fmod
				-- core
				'{COPY} "%{prj.name}\\lib\\fmod\\api\\core\\lib\\x64\\fmod.dll" "%{cfg.buildtarget.directory}"',
				-- bank
				'{COPY} "%{prj.name}\\lib\\fmod\\api\\fsbank\\lib\\x64\\fsbank.dll" "%{cfg.buildtarget.directory}"',
				'{COPY} "%{prj.name}\\lib\\fmod\\api\\fsbank\\lib\\x64\\libfsbvorbis64.dll" "%{cfg.buildtarget.directory}"',
				'{COPY} "%{prj.name}\\lib\\fmod\\api\\fsbank\\lib\\x64\\opus.dll" "%{cfg.buildtarget.directory}"',
				-- studio
				'{COPY} "%{prj.name}\\lib\\fmod\\api\\studio\\lib\\x64\\fmodstudio.dll" "%{cfg.buildtarget.directory}"',
			-- resources
				'{COPY} "%{prj.name}\\res\\animation\\**" "%{cfg.buildtarget.directory}\\Atom\\res\\animation"',
				'{COPY} "%{prj.name}\\res\\art\\**" "%{cfg.buildtarget.directory}\\Atom\\res\\art"',
				'{COPY} "%{prj.name}\\res\\audio\\**" "%{cfg.buildtarget.directory}\\Atom\\res\\audio"',
				'{COPY} "%{prj.name}\\res\\fonts\\**" "%{cfg.buildtarget.directory}\\Atom\\res\\fonts"',
				'{COPY} "%{prj.name}\\res\\levels\\**" "%{cfg.buildtarget.directory}\\Atom\\res\\levels"',
				'{COPY} "%{prj.name}\\res\\shaders\\**" "%{cfg.buildtarget.directory}\\Atom\\res\\shaders"'
		}

		buildoptions {
			-- multiprocessor compile switch enable 
			"/MP"
		}

		filter "configurations:Debug"
			linkoptions {
				"/SUBSYSTEM:CONSOLE"
			}
		filter "configurations:Release"
			linkoptions {
				"/SUBSYSTEM:WINDOWS"
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

