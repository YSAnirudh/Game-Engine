workspace "YSAoo-Engine"
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "YSAoo-Engine"
	location "YSAoo-Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	} 

	includedirs {
		"%{prj.name}/lib/"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"YSA_PLATFORM_WINDOWS",
			"YSA_BUILD_DLL",
			"_DEBUG",
			"_CONSOLE"
		}

	postbuildcommands {
		{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandboxApp"}
	}

	filter "configurations:Debug"
		define "YSA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		define "YSA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		define "YSA_DIST"
		optimize "On"

project "SandboxApp"
	location "SandboxApp"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	} 

	includedirs {
		"%{prj.name}/lib/",
		"YSAoo-Engine/src/"
	}

	links {
		"YSAoo-Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"YSA_PLATFORM_WINDOWS",
			"_DEBUG",
			"_CONSOLE"
		}

	filter "configurations:Debug"
		define "YSA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		define "YSA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		define "YSA_DIST"
		optimize "On"