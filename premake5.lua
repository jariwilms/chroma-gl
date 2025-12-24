project "chroma-gl"
	location         "chroma-gl"
	language         "C++"
	cppdialect       "C++23"
	kind             "StaticLib"
	staticruntime    "On"
	enablemodules    "On"
	buildstlmodules  "On"
	warnings         "Extra"
	externalwarnings "Off"
	
	includedirs {
		"chroma-gl/source"   , 
		
		"vendor/glad/include", 
		"vendor/glm/include" , 
		"vendor/rgfw/include", 
		"vendor/stb/include" , 
	}
	files {
		"chroma-gl/**.ixx", 	
	}
	links {
		"glad"        , 
		"glm"         , 
		"rgfw"        , 
		"stb"         , 
		
		"opengl32.lib", 
	}
	
	defines {
		"RGFW_IMPLEMENTATION", 
		"RGFW_OPENGL", 
	}
	
	filter "configurations:Debug"
		defines  { "BUILD_CONFIGURATION=debug", }
	filter "configurations:Release"
		defines  { "BUILD_CONFIGURATION=release", }

	-- @brief Visual Studio: Bugfix for conflicting C++ module names
	-- Credit goes to larioteo
	-- https://github.com/premake/premake-core/issues/2177

	require("vstudio")
	premake.override(premake.vstudio.vc2010.elements, "clCompile", function(base, prj)
		local m     = premake.vstudio.vc2010
		local calls = base(prj)
		
		if premake.project.iscpp(prj) then 
			table.insertafter(calls, premake.xmlDeclaration,  function()
				premake.w('<ModuleDependenciesFile>$(IntDir)\\%%(RelativeDir)</ModuleDependenciesFile>')
				premake.w('<ModuleOutputFile>$(IntDir)\\%%(RelativeDir)</ModuleOutputFile>')
				premake.w('<ObjectFileName>$(IntDir)\\%%(RelativeDir)</ObjectFileName>')
			end)
		end

		return calls
	end)

group "Vendor"
include "vendor/glad"
include "vendor/glm"
include "vendor/rgfw"
include "vendor/stb"
group ""
