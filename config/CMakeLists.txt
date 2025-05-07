message("Start to process Config.")

project(${CONFIG_NAME})

################################################################################
# Read source files
################################################################################
file(GLOB_RECURSE INI_FILES ${PROJECT_SOURCE_DIR}/*.ini)

set(ALL_FILES ${INI_FILES})
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
# Create Target
################################################################################
add_custom_target(${PROJECT_NAME} SOURCES ${ALL_FILES})
message("Processing Config finished.")
