project "rgfw"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	files { "include/rgfw/rgfw.h", "include/rgfw/rgfw.c" }

	usage "PUBLIC"
		includedirs { "include" }
	usage "INTERFACE"
		links { "rgfw" }
