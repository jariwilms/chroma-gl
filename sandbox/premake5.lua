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
    includedirs { "%{wks.location}/chroma-gl/source", "%{wks.location}/sandbox" }
    files       { "**.hpp", "**.cpp", "**.ixx" }
    links       { "chroma-gl" }
