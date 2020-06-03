cmake_minimum_required(VERSION 3.13)

set(LIBRARY_USE_MODE "HEADER_ONLY" CACHE STRING "How the example programs are to use the stacktrace library")
set_property(CACHE LIBRARY_USE_MODE PROPERTY STRINGS HEADER_ONLY LINKED)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
enable_language(CXX)
include(CompileWithWarnings)

find_package(Boost 1.65.0 COMPONENTS filesystem REQUIRED)

set(examples
	plain_vanilla
	debug_function
	terminate_handler
	throwing_st
	trace_addresses
	user_config)
	
foreach(example ${examples})
	add_executable(${example} "${example}.cpp")
	target_link_libraries(${example} PRIVATE headers)
	if ("${LIBRARY_USE_MODE}" STREQUAL "LINKED")
		target_link_libraries(${example} PRIVATE ${library_targets})
		# TODO: Use ternary IF here...
		if (BUILD_DYNAMIC)
			target_compile_definitions(${example} PRIVATE STRACKTRACE_DYN_LINK)
		else()
			target_compile_definitions(${example} PRIVATE STRACKTRACE_LINK)
		endif()
	endif()
	set_property(TARGET ${example} PROPERTY CXX_STANDARD 11) # Should I use 14 instead?
	set_property(TARGET ${example} PROPERTY CXX_STANDARD_REQUIRED ON)
	set_property(TARGET ${example} PROPERTY CXX_EXTENSIONS OFF)
endforeach()
target_sources(user_config PRIVATE user_config.hpp)

target_link_libraries(plain_vanilla PRIVATE ${Backtrace_LIBRARY} ${Backtrace_LIBRARIES} "-lbacktrace")
target_link_libraries(terminate_handler PRIVATE Boost::boost Boost::filesystem rt)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
