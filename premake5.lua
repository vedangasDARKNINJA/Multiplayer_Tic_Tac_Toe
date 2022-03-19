newoption 
{
   trigger = "opengl43",
   description = "use OpenGL 4.3"
}

workspace "GameEngine"
	configurations { "Debug","Debug.DLL", "Release", "Release.DLL" }
	platforms { "x64", "x86"}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Debug.DLL"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter "configurations:Release.DLL"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
		
	filter { "platforms:x86" }
		architecture "x86"
	
	filter{}
	
	location "build"

include "dependencies/raylib"

project "Game"
	kind "ConsoleApp"
	location "%{_MAIN_SCRIPT_DIR}/build/%{prj.name}"
	language "C++"
	cppdialect "C++17"
	
	targetdir "%{_MAIN_SCRIPT_DIR}/build/bin/%{cfg.buildcfg}"
	objdir "%{_MAIN_SCRIPT_DIR}/build/bin-int/%{cfg.buildcfg}"
	debugdir "%{_MAIN_SCRIPT_DIR}/"
		
	files {"src/**.c", "src/**.cpp", "src/**.h"}

	links {"raylib"}
	
	includedirs { "src", "dependencies/raylib/src" }
	
	defines{"PLATFORM_DESKTOP"}
	if (_OPTIONS["opengl43"]) then
		defines{"GRAPHICS_API_OPENGL_43"}
	else
		defines{"GRAPHICS_API_OPENGL_33"}
	end
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		dependson {"raylib"}
		links {"raylib.lib"}
        characterset ("MBCS")
		
	filter "system:windows"
		defines{"_WIN32"}
		links {"winmm", "kernel32", "opengl32", "kernel32", "gdi32"}
		libdirs {"%{_MAIN_SCRIPT_DIR}/build/bin/%{cfg.buildcfg}"}
		
	filter "system:linux"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
		
	filter {}