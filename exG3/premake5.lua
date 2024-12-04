workspace "COMP3811-glcode"
	language "C++"
	cppdialect "C++20"

	platforms { "x64" }
	configurations { "debug", "release" }

	flags "NoPCH"
	flags "MultiProcessorCompile"

	startproject "exercise3"

	debugdir "%{wks.location}"
	objdir "_build_/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.toolset}"
	targetsuffix "-%{cfg.buildcfg}-%{cfg.platform}-%{cfg.toolset}"
	
	-- Default toolset options
	filter "toolset:gcc or toolset:clang"
		linkoptions { "-pthread" }
		buildoptions { "-march=native", "-Wall", "-pthread" }

		-- Varriable-length arrays (VLAs) are an extension that GCC and clang
		-- have long supported. However, they are not part of the C++ standard.
		-- (MSVC will not compile code with VLAs.)
		buildoptions { "-Werror=vla" }

	filter "toolset:msc-*"
		warnings "extra" -- this enables /W4; default is /W3
		--buildoptions { "/W4" }
		buildoptions { "/utf-8" }
		buildoptions { "/permissive-" }
		defines { "_CRT_SECURE_NO_WARNINGS=1" }
		defines { "_SCL_SECURE_NO_WARNINGS=1" }

		buildoptions {
			"/wd4456", -- declaration of 'foo' hides previous local declaration
		}

	filter "*"

	-- default libraries
	filter "system:linux"
		links "dl"
	
	filter "system:windows"
		links "OpenGL32"

	filter "*"

	-- default outputs
	filter "kind:StaticLib"
		targetdir "lib/"

	filter "kind:ConsoleApp"
		targetdir "bin/"
		targetextension ".exe"
	
	filter "*"

	--configurations
	filter "debug"
		symbols "On"
		defines { "_DEBUG=1" }

	filter "release"
		optimize "On"
		defines { "NDEBUG=1" }

	filter "*"

-- Third party dependencies
include "third_party" 

-- Projects
project "exercise3"
	local sources = { 
		"exercise3/**.cpp",
		"exercise3/**.hpp",
		"exercise3/**.hxx",
		"exercise3/**.inl"
	}

	kind "ConsoleApp"
	location "exercise3"

	files( sources )

	dependson "exercise3-shaders"

	links "vmlib"
	links "support"

	links "x-stb"
	links "x-glad"
	links "x-glfw"

project "exercise3-shaders"
	local shaders = { 
		"assets/ex3/*.vert",
		"assets/ex3/*.frag",
		"assets/ex3/*.geom",
		"assets/ex3/*.tesc",
		"assets/ex3/*.tese",
		"assets/ex3/*.comp"
	}

	kind "Utility"
	location "assets/ex3"

	files( shaders )

project "vmlib-test"
	local sources = { 
		"vmlib-test/**.cpp",
		"vmlib-test/**.hpp",
		"vmlib-test/**.hxx",
		"vmlib-test/**.inl"
	}

	kind "ConsoleApp"
	location "vmlib-test"

	files( sources )

	links "vmlib"

	links "x-catch2"

project "support"
	local sources = { 
		"support/**.cpp",
		"support/**.hpp",
	}

	kind "StaticLib"
	location "support"

	files( sources )

	filter "*"

project "vmlib"
	local sources = { 
		"vmlib/**.cpp",
		"vmlib/**.hpp",
		"vmlib/**.hxx",
		"vmlib/**.inl"
	}

	kind "StaticLib"
	location "vmlib"

	files( sources )


--EOF
