project "chroma-gl"
	language         "C++"
	cppdialect       "C++23"
	kind             "StaticLib"
	staticruntime    "On"
	enablemodules    "On"
	buildstlmodules  "On"
	warnings         "Extra"
	externalwarnings "Off"

	files { "source/**.ixx" }

	usage "PUBLIC"
		uses        { "glad", "glm", "rgfw", "stb" }
		includedirs { "source" }
		links       { "opengl32.lib" }

		filter "configurations:Debug"
			defines { "BUILD_CONFIGURATION=debug" }
		filter "configurations:Release"
			defines { "BUILD_CONFIGURATION=release" }
		filter {}
	usage "INTERFACE"
		links { "chroma-gl" }
