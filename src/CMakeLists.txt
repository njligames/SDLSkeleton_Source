list(APPEND TARGET_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/cpp)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.c*)
file(GLOB_RECURSE HDRS ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.h)

set( TARGET_PROJECT_SOURCES ${TARGET_PROJECT_SOURCES} ${SRCS} ${HDRS} )
set( TARGET_RESOURCES ${TARGET_RESOURCES} ${ASSET_CATALOGUE} )

file(GLOB_RECURSE SRCS_TEST_CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
file(GLOB_RECURSE SRCS_TEST_C ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c)
file(GLOB_RECURSE HDRS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/*.h)

set( TARGET_PROJECT_SOURCES_TEST ${SRCS_TEST_CPP} ${SRCS_TEST_C} ${HDRS_TEST} )

add_subdirectory(platform)

if(NOT ANDROID AND BUILD_DOC)
    add_subdirectory(doc)
endif()

# add_subdirectory(swig)

