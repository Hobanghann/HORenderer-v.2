message("Start to process app")

project(${APP_NAME})

################################################################################
# Read source files
################################################################################
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE RESOURCES 
    ${PROJECT_SOURCE_DIR}/res/*.h
    ${PROJECT_SOURCE_DIR}/res/*.rc
    ${PROJECT_SOURCE_DIR}/res/*.ico)

set(ALL_FILES ${SOURCES} ${HEADERS} ${RESOURCES})
################################################################################
# Repackiging source files
################################################################################
foreach(FILE ${ALL_FILES})
    # make rel path
	file(RELATIVE_PATH REL_PATH "${PROJECT_SOURCE_DIR}" "${FILE}")
	set(ALL_FILES_REL ${ALL_FILES_REL} ${REL_PATH})
endforeach()	

set_source_files_properties(${ALL_FILES_REL} PROPERTIES HEADER_FILE_ONLY FALSE)

foreach(FILE ${ALL_FILES_REL})
    # get the base path
    get_filename_component(BASE_PATH "${FILE}" PATH)

    # changes /'s to \\'s
    string(REPLACE "/" "\\" GROUP "${BASE_PATH}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
################################################################################
# ExcutableOutput Setting
################################################################################
add_executable(${PROJECT_NAME} WIN32 ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
	PREFIX ""
	OUTPUT_NAME ${MAIN_PROJECT_NAME}
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
	VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/resource
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)
################################################################################
# Visual Studio Setting
################################################################################
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")
################################################################################
# Include directory
################################################################################
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
	)
    
################################################################################
# Import Library
################################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC ${THIRD_PARTY_DUMMY} ${TOOLS_NAME} ${CORE_NAME} ${GRAPHICS_NAME} ${SCENE_NAME} ${RENDERER_NAME} ${WINDOWS_NAME})

################################################################################
# Copy Resources
################################################################################
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
  set(RESOURCE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/resource)

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resource
    ${RESOURCE_OUTPUT_DIR}
  )
endforeach()
get_target_property(INCS ${PROJECT_NAME} INCLUDE_DIRECTORIES)
message(STATUS "Include dirs of app: ${INCS}")
message("Processing app finished")