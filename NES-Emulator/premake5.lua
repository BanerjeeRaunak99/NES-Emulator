workspace "NES-Emulator"
	architecture "x86"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

project "NES-Emulator"
	location "NES-Emulator"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"NES-Emulator/src/**.h",
		"NES-Emulator/src/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:*"
		defines { "SFML_STATIC" }
		includedirs { "NES-Emulator/dependencies/SFML/include" }
		libdirs { "NES-Emulator/dependencies/SFML/lib" }
		links
		{
			"opengl32",
			"freetype",
			"winmm",
			"gdi32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg",
			"ws2_32"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		links
		{	
			"sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-system-s-d",
			"sfml-audio-s-d",
			"sfml-network-s-d"
		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		links
		{	
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			"sfml-audio-s",
			"sfml-network-s"
		}
