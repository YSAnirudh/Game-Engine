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

	targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/lib/**.h",
		"%{prj.name}/lib/**.cpp"
	} 

	includedirs {
		"%{prj.name}/lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"YSA_PLATFORM_WINDOWS",
			"YSA_BUILD_DLL"
		}

	postbuildcommands {
		{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandboxApp"}
	}

	filter "configurations:Debug"
		defines "YSA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "YSA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "YSA_DIST"
		optimize "On"

project "SandboxApp"
	location "SandboxApp"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	} 

	includedirs {
		"YSAoo-Engine/lib",
		"YSAoo-Engine/src"
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
		}

	filter "configurations:Debug"
		defines "YSA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "YSA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "YSA_DIST"
		optimize "On"