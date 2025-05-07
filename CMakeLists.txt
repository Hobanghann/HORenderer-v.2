##########################################################
# CMake Settings for HOrenderer
##########################################################

cmake_minimum_required(VERSION 3.4)
include(FetchContent)
set(MAIN_PROJECT_NAME HORenderer)

project(${MAIN_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##########################################################
# Check Platform
##########################################################
if(NOT WIN32)
	message(FATAL_ERROR "This project only supports windows environment currently.")
endif()

if(NOT MSVC)
	message(FATAL_ERROR "This project only supports MSVC project currently.")
endif()

set(PLATFORM_DEFINITION PLATFORM_GENERIC)
set(PLATFORM_FOLDER Generic)

option(TARGET_WINDOWS "Windows Option" ON)

if(TARGET_WINDOWS)
	set(PLATFORM_DEFINITION PLATFORM_WINDOWS)
	set(PLATFORM_FOLDER Windows)
endif()

##########################################################
# Set Sub Project's Name
##########################################################
set(CONFIG_NAME Config)
set(RESOURCE_NAME Resource)
set(THIRD_PARTY_NAME ThirdParty)
set(THIRD_PARTY_DUMMY TP_DUMMY)
set(TOOLS_NAME Tools)
set(CORE_NAME Core)
set(GRAPHICS_NAME Graphics)
set(SCENE_NAME Scene)
set(RENDERER_NAME Renderer)
set(WINDOWS_NAME Windows)
set(APP_NAME App)

##########################################################
# Process Sub Projects
##########################################################
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/config)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/resource)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tools)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/graphics)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/scene)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)

message("Cmake finished")