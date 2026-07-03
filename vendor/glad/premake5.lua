project "glad"
	language      "C++"
	cppdialect    "C++23"
	kind          "StaticLib"
	staticruntime "On"
	enablemodules "On"
	warnings      "Off"
	
	files { "include/glad/**.h", "include/glad/**.c", "include/glad/**.ixx" }
	
	filter "files:**.c"
        compileas "C"
    filter {}
	
	usage "PUBLIC"
		includedirs { "include" }
	usage "INTERFACE"
		links { "glad" }
