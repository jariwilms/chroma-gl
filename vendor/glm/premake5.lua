project "glm"
	language        "C++"
	cppdialect      "C++23"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "On"
	buildstlmodules "On"
	warnings        "Off"
	
	files { "include/glm/**.hpp", "include/glm/**.cpp", "include/glm/**.inl", "module/glm/**.ixx" }
	
	usage "PUBLIC"
		defines     { "GLM_ENABLE_EXPERIMENTAL", "GLM_GTC_INLINE_NAMESPACE", "GLM_EXT_INLINE_NAMESPACE", "GLM_GTX_INLINE_NAMESPACE", "GLM_FORCE_SIZE_T_LENGTH" }
		includedirs { "include", "module" }
	usage "INTERFACE"
		links { "glm" }
