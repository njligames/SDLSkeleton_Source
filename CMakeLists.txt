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

if(EMSCRIPTEN)
    list(APPEND TARGET_DEFINITIONS "__EMSCRIPTEN__=1")
    if(VR)
        list(APPEND TARGET_DEFINITIONS "__VR__=1")
    endif()
elseif(WIN32)
    if(ARCH_64)
        list(APPEND TARGET_DEFINITIONS "__WINDOWS64__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    else()
        list(APPEND TARGET_DEFINITIONS "__WINDOWS32__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    endif()
elseif(APPLE)
    if(IOS)
        list(APPEND TARGET_DEFINITIONS "__IPHONEOS__=1")
        if(VR)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    elseif(TVOS)
        list(APPEND TARGET_DEFINITIONS "__APPLETVOS__=1")
    else()
        list(APPEND TARGET_DEFINITIONS "__MACOSX__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    if(LINUX)
        list(APPEND TARGET_DEFINITIONS "__LINUX__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    elseif(UNIX)
        list(APPEND TARGET_DEFINITIONS "__UNIX__=1")
    endif()
elseif(ANDROID)
    list(APPEND TARGET_DEFINITIONS "__ANDROID__=1")

    add_library(hidapi UNKNOWN IMPORTED)
    add_library(main UNKNOWN IMPORTED)
    add_library(SDL2 UNKNOWN IMPORTED)

    set_target_properties(SDL2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${THIRDPARTY_DIR}/includes/SDL2")

    set_property(TARGET hidapi APPEND PROPERTY IMPORTED_LOCATION  "${THIRDPARTY_DIR}/platform/android/${ANDROID_ABI}/libhidapi.so")
    set_property(TARGET main APPEND PROPERTY IMPORTED_LOCATION  "${THIRDPARTY_DIR}/platform/android/${ANDROID_ABI}/libmain.so")
    set_property(TARGET SDL2 APPEND PROPERTY IMPORTED_LOCATION  "${THIRDPARTY_DIR}/platform/android/${ANDROID_ABI}/libSDL2.so")

    list(APPEND TARGET_PROJECT_SOURCES "platform/android/native-lib.cpp")

    configure_file("${CMAKE_SOURCE_DIR}/../src/resources/platform/android/strings.xml.in" "${CMAKE_SOURCE_DIR}/../src/resources/platform/android/res/values/strings.xml")

    find_library( log-lib log)

    list(APPEND TARGET_LIBRARIES SDL2)
    list(APPEND TARGET_LIBRARIES hidapi)
    list(APPEND TARGET_LIBRARIES main)
    list(APPEND TARGET_LIBRARIES ${log-lib})
endif()

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

