
-- pick platform, Linux by default
local v_platform = iif ( os.is("windows"), "windows", "linux" )

--[[ This is a dummy option that must be included whenever you want to use the configuration option.
For the configuration, just type:
premake4 --config=debug --t=0 gmake ]]
--[[
newoption {
	trigger		= "t",
	value		= "none",
	description	= "test",
	allowed = {
		{ "0", "none" }
	}
}
]]

solution "LinusListix"
	configurations { "debug" }
	project "LinusListix"
		language( "C++" )
		if ( v_platform == "linux" ) then
			kind( "ConsoleApp" )
		else
			kind( "WindowedApp" )
		end
		files {
			"LinusListix.h",
			"debugger.cpp"
		}

		configuration "debug"
			objdir "obj/debug"
			targetdir "obj/debug"

