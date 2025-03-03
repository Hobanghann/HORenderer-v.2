message("Start to process app")

project(${APP_NAME})

################################################################################
# Read source files
################################################################################
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB RESOURCES 
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
	)
    
################################################################################
# Import Library
################################################################################
target_link_libraries(${PROJECT_NAME} ${MATH_NAME} ${ASSET_NAME} ${RENDERING_PIPELINE_NAME} ${ENGINE_NAME} ${RENDERER_NAME} ${WINDOWS_NAME})

message("Processing app finished")