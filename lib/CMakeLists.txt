message("Start to process Third Party.")

project(${THIRD_PARTY_NAME})

##########################################################
# Set External Libraries Name
##########################################################
set(ASSIMP_NAME assimp)
set(IMAGE_LOADER_NAME stb)
set(INI_PARSER_NAME inifile-cpp)
set(GTEST_NAME googletest)

##########################################################
# Download External Libraries
##########################################################

#Declare download targets

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/ CACHE PATH "Missing description." FORCE)
FetchContent_Declare(${ASSIMP_NAME}
GIT_REPOSITORY https://github.com/assimp/assimp.git
GIT_TAG master)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/ CACHE PATH "Missing description." FORCE)
FetchContent_Declare(${IMAGE_LOADER_NAME}
GIT_REPOSITORY https://github.com/nothings/stb.git
GIT_TAG master)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/ CACHE PATH "Missing description." FORCE)
FetchContent_Declare(${INI_PARSER_NAME}
GIT_REPOSITORY https://github.com/Rookfighter/inifile-cpp.git
GIT_TAG main)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/ CACHE PATH "Missing description." FORCE)
FetchContent_Declare(${GTEST_NAME}
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# FetchContent

message ("Start to Download " ${ASSIMP_NAME} "...")
FetchContent_MakeAvailable(${ASSIMP_NAME})
message ("Downloading " ${ASSIMP_NAME} " finished")

message ("Start to Download " ${IMAGE_LOADER_NAME} "...")
FetchContent_Populate(${IMAGE_LOADER_NAME})
message ("Downloading " ${IMAGE_LOADER_NAME} " finished")

message ("Start to Download " ${INI_PARSER_NAME} "...")
FetchContent_MakeAvailable(${INI_PARSER_NAME})
message ("Downloading " ${INI_PARSER_NAME} " finished")

message ("Start to Download " ${GTEST_NAME} "...")
FetchContent_MakeAvailable(${GTEST_NAME})
message ("Downloading " ${GTEST_NAME} " finished")



################################################################################
# Read source files
################################################################################
file(GLOB_RECURSE ALL_FILES ${PROJECT_SOURCE_DIR}/*)
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

add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
################################################################################
# Library Output Setting
################################################################################
add_library(${IMAGE_LOADER_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/${IMAGE_LOADER_NAME}.cc)
target_include_directories(${IMAGE_LOADER_NAME} INTERFACE ${${IMAGE_LOADER_NAME}_SOURCE_DIR})


add_library(${THIRD_PARTY_DUMMY} INTERFACE)
target_link_libraries(${THIRD_PARTY_DUMMY} INTERFACE ${ASSIMP_NAME} ${IMAGE_LOADER_NAME} inicpp)

add_library(${GTEST_NAME}_alias INTERFACE)
target_link_libraries(${GTEST_NAME}_alias INTERFACE GTest::gtest GTest::gtest_main)

message("Processing Third Party finished")
