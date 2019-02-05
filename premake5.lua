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
IncludeDirs["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDirs["glm"] = "Engine/vendor/glm"
IncludeDirs["spdlog"] = "Engine/vendor/spdlog/include"
IncludeDirs["stb"] = "Engine/vendor/stb"
IncludeDirs["obj_loader"] = "Engine/vendor/obj_loader"

include "Engine/vendor/GLAD"
include "Engine/vendor/GLFW"

project "COG"
	location "Engine"
	kind "SharedLib"
	language "C++"
	
	targetdir("%{prj.location}/bin/" .. output .. "/")
	objdir("%{prj.location}/bin-temp/" .. output .. "/")
	
	pchheader "precomp/precomp.h"
	pchsource "Engine/src/COG/precomp.cpp"
	
	files { 
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.hpp", 
		"%{prj.location}/src/**.h" 
	}
	
	includedirs{ 
		"%{IncludeDirs.spdlog}",
		"%{prj.location}/src",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.stb}",
		"%{IncludeDirs.obj_loader}"
	}
	
	links{
		"Glad",
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines { "COG_PLATFORM_WINDOWS", "COG_BUILD_DLL" }
		
	filter "configurations:Debug*"
		defines { "COG_DEBUG", "COG_ENABLE_ASSERTS" }
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release*"
		defines { "COG_RELEASE", "COG_ENABLE_ASSERTS" }
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist*"
		defines "COG_DIST"
		buildoptions "/MD"
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
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release*"
		defines "COG_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist*"
		defines "COG_DIST"
		buildoptions "/MD"
		optimize "On"