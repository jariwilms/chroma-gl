workspace "chroma-gl"
	startproject   "run"
	architecture   "x86_64"
	configurations { "Debug", "Release", }

	filter "configurations:Debug"
		runtime   "Debug"
		symbols   "On"
		targetdir "%{wks.location}/bin/debug/%{prj.name}"
		objdir    "%{wks.location}/build/debug/%{prj.name}"

	filter "configurations:Release"
		runtime   "Release"
		optimize  "Full"
		targetdir "%{wks.location}/bin/release/%{prj.name}"
		objdir    "%{wks.location}/build/release/%{prj.name}"



group "Application"
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
			"vendor/glfw/include", 
			"vendor/glm/include" , 
		    "vendor/stb/include" , 
		}
		files {
			"chroma-gl/**.ixx", 	
		}
		links {
			"glad"        , 
			"glfw"        , 
			"glm"         , 
			"stb"         , 
			
			"opengl32.lib", 
		}
		
		filter "configurations:Debug"
			defines { "BUILD_CONFIGURATION=debug", }
		filter "configurations:Release"
			sanitize { "Address" }
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



	project "run"
		location         "run"
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
			"run", 
		}
		files { 
			"run/**.hpp", 
			"run/**.cpp", 
		}
		links { 
			"chroma-gl", 
		}

		filter "configurations:Release"
			sanitize { "Address" }



group "Vendor"
	include "vendor/glad"
	include "vendor/glfw"
	include "vendor/glm"
	include "vendor/stb"
group ""