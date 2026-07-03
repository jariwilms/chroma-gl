project "stb"
	language      "C++"
	cppdialect    "C++23"
	kind          "StaticLib"
	staticruntime "On"
	enablemodules "On"
	warnings      "Off"
	
	defines { "STB_IMAGE_IMPLEMENTATION", "STB_IMAGE_READ_IMPLEMENTATION", "STB_IMAGE_WRITE_IMPLEMENTATION" }
	files   { "include/stb/stb_image.h", "include/stb/stb_image_write.h", "include/stb/**.ixx" }

	usage "PUBLIC"
		includedirs { "include" }
	usage "INTERFACE"
		links { "stb" }
