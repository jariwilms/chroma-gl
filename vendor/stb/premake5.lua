project "stb"
	language      "C"
	cdialect      "C23"
	kind          "StaticLib"
	staticruntime "On"
	warnings      "Off"
	
	files { "include/stb/stb_image.h", "include/stb/stb_image_write.h", "source/stb.c" }

	usage "PUBLIC"
		defines     { "STB_IMAGE_IMPLEMENTATION", "STB_IMAGE_WRITE_IMPLEMENTATION" }
		includedirs { "include" }
	usage "INTERFACE"
		links { "stb" }
