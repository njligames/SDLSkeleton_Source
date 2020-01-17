# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

project(SDLSkeleton)

set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")

add_library(hidapi UNKNOWN IMPORTED)
add_library(main UNKNOWN IMPORTED)
add_library(SDL2 UNKNOWN IMPORTED)

set_target_properties(SDL2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${THIRDPARTY_DIR}/includes/SDL2")

SET(PROJECT_SOURCES "main.cpp")

if(ANDROID)
    set_property(TARGET hidapi APPEND PROPERTY IMPORTED_LOCATION  "${THIRDPARTY_DIR}/platform/android/${ANDROID_ABI}/libhidapi.so")
    set_property(TARGET main APPEND PROPERTY IMPORTED_LOCATION  "${THIRDPARTY_DIR}/platform/android/${ANDROID_ABI}/libmain.so")
    set_property(TARGET SDL2 APPEND PROPERTY IMPORTED_LOCATION  "${THIRDPARTY_DIR}/platform/android/${ANDROID_ABI}/libSDL2.so")

    list(APPEND PROJECT_SOURCES "platform/android/native-lib.cpp")

    configure_file("${CMAKE_SOURCE_DIR}/../resources/platform/android/strings.xml.in" "${CMAKE_SOURCE_DIR}/../resources/platform/android/res/values/strings.xml")


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

    add_library( # Sets the name of the library.
            native-lib

            # Sets the library as a shared library.
            SHARED

            # Provides a relative path to your source file(s).
            ${PROJECT_SOURCES})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

    find_library( # Sets the name of the path variable.
            log-lib

            # Specifies the name of the NDK library that
            # you want CMake to locate.
            log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

    target_link_libraries( # Specifies the target library.
            native-lib

            SDL2
            hidapi
            main

            # Links the target library to the log library
            # included in the NDK.
            ${log-lib})
endif()

if(IOS)
endif()


if(NOT ANDROID)
    enable_testing()
    add_subdirectory(test)
endif()
