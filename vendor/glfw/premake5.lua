project "glfw"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	includedirs {
		"include", 
		"src", 
	}
	files {
		"include/**", 
		"src/**", 
	}
	
	filter "system:windows"
		defines { "_GLFW_WIN32", }
