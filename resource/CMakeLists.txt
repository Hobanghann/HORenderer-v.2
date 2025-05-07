message("Start to process Resource.")

project(${RESOURCE_NAME})

################################################################################
# Read source files
################################################################################
file(GLOB_RECURSE OBJ_FILES ${PROJECT_SOURCE_DIR}/*.obj)
file(GLOB_RECURSE MTL_FILES ${PROJECT_SOURCE_DIR}/*.mtl)
file(GLOB_RECURSE IMAGES ${PROJECT_SOURCE_DIR}/*.jpg ${PROJECT_SOURCE_DIR}/*.jpeg ${PROJECT_SOURCE_DIR}/*.png ${PROJECT_SOURCE_DIR}/*.bmp ${PROJECT_SOURCE_DIR}/*.dds)

set(ALL_FILES ${OBJ_FILES} ${MTL_FILES} ${IMAGES})
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
message("Processing Resource finished")
