message("Start to Graphics module renderer")

project(${GRAPHICS_NAME})

################################################################################
# Read source files
################################################################################
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/*.h)

set(ALL_FILES ${SOURCES} ${HEADERS})
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
# Library Output Setting
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
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
target_link_libraries(${PROJECT_NAME} PUBLIC ${THIRD_PARTY_DUMMY} ${TOOLS_NAME} ${CORE_NAME})
message("Processing Graphics module finished")
