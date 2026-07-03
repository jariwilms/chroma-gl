project "rgfw"
	language      "C++"
	cppdialect    "C++23"
	kind          "StaticLib"
	staticruntime "On"
	enablemodules "On"
	warnings      "Off"
	
	defines { "RGFW_IMPLEMENTATION" }
	files   { "include/rgfw/**.h", "include/rgfw/**.ixx" }

	usage "PUBLIC"
		uses        { "glad", "glm" }
		defines     { "RGFW_OPENGL" }
		includedirs { "include" }
	usage "INTERFACE"
		links { "rgfw" }
