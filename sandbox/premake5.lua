project "sandbox"
    language         "C++"
    cppdialect       "C++23"
    kind             "ConsoleApp"
    staticruntime    "On"
    enablemodules    "On"
    buildstlmodules  "On"
    warnings         "Extra"
    externalwarnings "Off"
	
	uses        { "chroma-gl" }
    includedirs { "%{wks.location}/sandbox/source" }
    files       { "source/**.hpp", "source/**.cpp", "source/**.ixx" }
