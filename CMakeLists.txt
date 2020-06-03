# ---------------------------
# CMake modules and settings
# ---------------------------

cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(CheckIncludeFiles)
include(CheckTypeSize)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckCSourceCompiles)
include(TestBigEndian)

# ----------------------
# Project & build type settings
# ----------------------

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release" )
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

PROJECT(
	stacktrace
	LANGUAGES CXX
	DESCRIPTION "De-boostified variant of Antony Polukhin's Boost Stacktrace library"
	HOMEPAGE_URL https://github.com/eyalroz/stacktrace
	VERSION 1.73.0.1 # Following the Boost version, plus a quaternary version indicator for ourselves
)

# ---------------------
# Project options
# ---------------------

option(BUILD_DYNAMIC "Build dynamic libraries" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_BACKTRACE_LIB "Build backtrace library" ON)
option(BUILD_WINDBG_LIB "Build windbg library" OFF)
option(BUILD_WINDBG_CACHED_LIB "Build windbg_cached library" OFF)

# Options to incorporate: STACKTRACE_LINK , STACKTRACE_DYN_LINK

# ---------------------
# Package dependencies
# ---------------------

find_package(Threads REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
if (${BUILD_BACKTRACE_LIB})
	find_package(Backtrace REQUIRED) # This behaves weirdly
endif()

# TODO: Which libraries should be shared, if any? 


add_library(headers INTERFACE) # A header-only library!
target_compile_features(headers INTERFACE cxx_std_11) # This means _at least_ C++11
target_include_directories(
	headers
	INTERFACE
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(headers INTERFACE ${CMAKE_DL_LIBS})

# TODO: Enable warnings during compilation

set(library_targets
	noop
	addr2line
	basic)
if (${BUILD_WINDBG_LIB})
	list(APPEND library_targets windbg)
endif()
if (${BUILD_WINDBG_CACHED_LIB})
	list(APPEND library_targets windbg_cached)
endif()
if (${BUILD_BACKTRACE_LIB})
	list(APPEND library_targets backtrace)
endif()

foreach(target ${library_targets})
	if(BUILD_DYNAMIC)
		add_library(${target} SHARED)
	else()
		add_library(${target})
	endif()
	target_sources(${target} PRIVATE src/${target}.cpp)
    set_target_properties(${target} PROPERTIES OUTPUT_NAME "stacktrace_${target}")	
	set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})
	set_property(TARGET ${target} PROPERTY CXX_STANDARD 11) # Should I use 14 instead?
	set_property(TARGET ${target} PROPERTY CXX_STANDARD_REQUIRED ON)
	set_property(TARGET ${target} PROPERTY CXX_EXTENSIONS OFF)
	target_link_libraries(${target} PUBLIC headers)
endforeach()

target_link_libraries(addr2line PUBLIC Threads::Threads)
target_link_libraries(basic     PUBLIC Threads::Threads)
if (${BUILD_BACKTRACE_LIB})
	target_link_libraries(backtrace PUBLIC Threads::Threads ${Backtrace_LIBRARY} ${Backtrace_LIBRARIES})
endif()

#TODO: check-target-builds for backtrace, addr2line, windbg, WinDbgCached


if (BUILD_EXAMPLES)
	add_subdirectory(example)
endif()

# -------------------------
# Installation
# -------------------------

include(GNUInstallDirs)

install(
	TARGETS headers ${library_targets}
	EXPORT stracktrace_export
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
	DIRECTORY include/
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
	EXPORT stracktrace_export
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/stacktrace"
	NAMESPACE "stacktrace::"
	FILE "stacktrace-config.cmake"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"stacktrace-config-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMinorVersion
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/stacktrace-config-version.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/stacktrace"
)

