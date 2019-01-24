workspace "COG"
	configurations { 
		"Debug32", "Debug64", "Release32", "Release64", "Dist32", "Dist64" 
	}

	filter "configurations:*32"
		architecture "x86"
	
	filter "configurations:*64"
		architecture "x64"
		

output = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLAD"] = "Engine/vendor/GLAD/include"

include "Engine/vendor/GLAD"

project "COG"
	location "Engine"
	kind "SharedLib"
	language "C++"
	
	targetdir("%{prj.location}/bin/" .. output .. "/")
	objdir("%{prj.location}/bin-temp/" .. output .. "/")
	
	files { 
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.hpp", 
		"%{prj.location}/src/**.h" 
	}
	
	includedirs{ 
		"%{prj.location}/vendor/spdlog/include",
		"%{prj.location}/src",
		"%{IncludeDirs.GLAD}"
	}
	
	links{
		"Glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines { "COG_PLATFORM_WINDOWS", "COG_BUILD_DLL" }
		
	filter "configurations:Debug*"
		defines "COG_DEBUG"
		symbols "On"
		
	filter "configurations:Release*"
		defines "COG_RELEASE"
		optimize "On"
		
	filter "configurations:Dist*"
		defines "COG_DIST"
		optimize "On"

project "Test"
	location "Tester"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("%{prj.location}/bin/" .. output .. "/")
	objdir("%{prj.location}/bin-temp/" .. output .. "/")
	
	files { 
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.hpp", 
		"%{prj.location}/src/**.h" 
	}
	
	includedirs{ 
		"Engine/vendor/spdlog/include",
		"Engine/src"
	}
	
	links { "COG" }
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines { "COG_PLATFORM_WINDOWS" }
		
		postbuildcommands { "$(SolutionDir)copy_dll.bat " .. output }
		
	filter "configurations:Debug*"
		defines "COG_DEBUG"
		symbols "On"
		
	filter "configurations:Release*"
		defines "COG_RELEASE"
		optimize "On"
		
	filter "configurations:Dist*"
		defines "COG_DIST"
		optimize "On"