project "Glad"
	
	kind "StaticLib"
	language("C")
	
	targetdir("%{prj.location}/bin/" .. output .. "/")
	objdir("%{prj.location}/bin-temp/" .. output .. "/")
	
	files{
		"include/glad/glad.h", "include/KHR/khrplatform.h", "src/glad.c"
	}
	
	includedirs{
		"include"
	}
	
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		
	filter { "system:windows", "configurations:Release*" }
		buildoptions "/MT"