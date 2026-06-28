include "premake5.lua"

project "sandbox"
    location         "sandbox"
    language         "C++"
    cppdialect       "C++23"
    kind             "ConsoleApp"
    staticruntime    "On"
    enablemodules    "On"
    buildstlmodules  "On"
    warnings         "Extra"
    externalwarnings "Off"
    includedirs {
        "chroma-gl/source",
        "sandbox",
    }
    files {
        "sandbox/**.hpp",
        "sandbox/**.cpp",
		"sandbox/**.ixx",
    }
    links {
        "chroma-gl",
    }

workspace "chroma-gl"
    startproject "sandbox"
