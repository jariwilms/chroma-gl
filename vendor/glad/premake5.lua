project "glad"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	files { "include/glad/gl.h", "source/gl.c" }
	
	usage "PUBLIC"
		includedirs { "include" }
	usage "INTERFACE"
		links { "glad" }
