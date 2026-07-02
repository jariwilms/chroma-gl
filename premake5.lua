newoption {
    trigger     = "sandbox",
    description = "Build the sandbox project"
}

workspace "chroma-gl"
    architecture   "x86_64"
    configurations { "Debug", "Release" }
	
	if _OPTIONS["sandbox"] then
        startproject "sandbox"
    else
        startproject "chroma-gl"
    end
	
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
    filter {}

group "vendor"
    include "vendor/glad"
    include "vendor/glm"
    include "vendor/rgfw"
    include "vendor/stb"
group ""

include "chroma-gl"

if _OPTIONS["sandbox"] then
    include "sandbox"
end

if not premake._moduleOutputOverrideApplied then
    premake._moduleOutputOverrideApplied = true
	
	require("vstudio")
	premake.override(premake.vstudio.vc2010.elements, "clCompile", function(base, prj)
		local m     = premake.vstudio.vc2010
		local calls = base(prj)
		if premake.project.iscpp(prj) then
			table.insertafter(calls, premake.xmlDeclaration, function()
				premake.w('<ModuleDependenciesFile>$(IntDir)\\%%(RelativeDir)</ModuleDependenciesFile>')
				premake.w('<ModuleOutputFile>$(IntDir)\\%%(RelativeDir)</ModuleOutputFile>')
				premake.w('<ObjectFileName>$(IntDir)\\%%(RelativeDir)</ObjectFileName>')
			end)
		end
		return calls
	end)
end
