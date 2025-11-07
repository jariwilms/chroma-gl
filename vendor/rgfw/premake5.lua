project "rgfw"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	includedirs {
		"include", 
	}
	files {
		"include/rgfw/rgfw.h", 
		"include/rgfw/rgfw.c", 
	}
