project "imgui"
	language        "C++"
	cppdialect      "C++23"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "On"
	buildstlmodules "On"
	warnings        "Off"
	
	defines {
		
	}
	includedirs {
		"include", 
	}	
	files {
		"include/imgui/**.h", 
		"include/imgui/**.cpp", 
	}
