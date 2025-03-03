##########################################################
# CMake Settings for HOrenderer
##########################################################

cmake_minimum_required(VERSION 3.4)

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
# Sub Project's Name
##########################################################
set(MATH_NAME MathModule)
set(ASSET_NAME AssetModule)
set(RENDERING_PIPELINE_NAME RenderingPipelineModule)
set(ENGINE_NAME EngineModule)
set(RENDERER_NAME RendererModule)
set(WINDOWS_NAME WindowsModule)
set(APP_NAME AppModule)

##########################################################
# Sub Projects
##########################################################
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/asset)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/rendering_pipeline)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)

message("Cmake finished")