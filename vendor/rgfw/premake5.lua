project "rgfw"
	language      "C++"
	cppdialect    "C++23"
	kind          "StaticLib"
	staticruntime "On"
	enablemodules "On"
	warnings      "Off"
	
	defines { "RGFW_IMPLEMENTATION" }
	files   { "include/rgfw/**.h", "module/rgfw/**.ixx" }

	usage "PUBLIC"
		uses        { "glad", "glm" }
		defines     { "RGFW_OPENGL" }
		includedirs { "include", "module" }
	usage "INTERFACE"
		links { "rgfw" }
