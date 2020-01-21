# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

project(SDLSkeleton)

set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(TARGET_DEFINITIONS "")
set(TARGET_LIBRARIES "")
SET(TARGET_MAIN_SOURCES "main.cpp")
SET(TARGET_PROJECT_SOURCES "")

add_subdirectory(platform)

if(ANDROID)
    add_library(native-lib SHARED ${TARGET_PROJECT_SOURCES} ${TARGET_MAIN_SOURCES})
    target_compile_definitions(native-lib PUBLIC ${TARGET_DEFINITIONS})
    target_link_libraries( native-lib ${TARGET_LIBRARIES})
else()
    add_executable(${CMAKE_PROJECT_NAME} SHARED ${TARGET_PROJECT_SOURCES} ${TARGET_MAIN_SOURCES})
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ${TARGET_DEFINITIONS})
    target_link_libraries( ${CMAKE_PROJECT_NAME} ${TARGET_LIBRARIES})

    enable_testing()
    add_subdirectory(test)
endif()

