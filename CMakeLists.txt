cmake_minimum_required(VERSION 3.10.2)

project(SDLSkeleton VERSION 1.0.0.0)

set(BUILD_DOC OFF CACHE BOOL "Build the documentation")
set(BUILD_TEST OFF CACHE BOOL "Build the tests")

include(CheckCXXCompilerFlag)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/cmake/detectGL.cmake)

# cmake_policy(SET CMP0078 OLD)
# cmake_policy(SET CMP0086 OLD)



CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(TARGET_EXECUTABLE_NAME "PLACEHOLDER" CACHE STRING "The name of the executable")
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(TARGET_DEFINITIONS "")
set(TARGET_MAIN_SOURCES "${CMAKE_SOURCE_DIR}/main.cpp")
set(TARGET_PLATFORM "none")
set(TARGET_BUNDLE_ID "com.njligames.engine.${CMAKE_PROJECT_NAME}")

set(BUILT_GTEST FALSE)

if(EMSCRIPTEN)
    set(BUILT_GTEST TRUE)

    set(TARGET_PLATFORM "emscripten")
    list(APPEND TARGET_DEFINITIONS "__EMSCRIPTEN__=1")
    if(VR)
        list(APPEND TARGET_DEFINITIONS "__VR__=1")
    endif()
elseif(WIN32)
    set(BUILT_GTEST TRUE)

    if(ARCH_64)
        set(TARGET_PLATFORM "windows64")
        list(APPEND TARGET_DEFINITIONS "__WINDOWS64__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    else()
        set(TARGET_PLATFORM "windows32")
        list(APPEND TARGET_DEFINITIONS "__WINDOWS32__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    endif()
elseif(APPLE)
    if(IOS)
        set(TARGET_PLATFORM "ios")
        list(APPEND TARGET_DEFINITIONS "__IPHONEOS__=1")
        if(VR)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    elseif(TVOS)
        set(TARGET_PLATFORM "appletvos")
        list(APPEND TARGET_DEFINITIONS "__APPLETVOS__=1")
    else()
        set(BUILT_GTEST TRUE)

        set(TARGET_PLATFORM "macos")
        list(APPEND TARGET_DEFINITIONS "__MACOS__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    endif()
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    set(BUILT_GTEST TRUE)

    if(CMAKE_SYSTEM_NAME MATCHES ".*Linux")
        cmake_policy(SET CMP0072 NEW)

        set(TARGET_PLATFORM "linux")
        list(APPEND TARGET_DEFINITIONS "__LINUX__=1")
        if(OCULUS)
            list(APPEND TARGET_DEFINITIONS "__VR__=1")
        endif()
    elseif(UNIX)
        set(TARGET_PLATFORM "unix")
        list(APPEND TARGET_DEFINITIONS "__UNIX__=1")
    endif()
elseif(ANDROID)
    set(TARGET_PLATFORM "android")
    list(APPEND TARGET_DEFINITIONS "__ANDROID__=1")
endif()

set(TARGET_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/assets")

# if(BUILT_GTEST)
# # Download and unpack googletest at configure time
#     configure_file(googletest.cmake.in
#             googletest-download/CMakeLists.txt)
#     execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#             WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#     execute_process(COMMAND ${CMAKE_COMMAND} --build .
#             WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#
# # Prevent GoogleTest from overriding our compiler/linker options
# # when building with Visual Studio
#     set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#
# # Add googletest directly to our build. This adds
# # the following targets: gtest, gtest_main, gmock
# # and gmock_main
#     add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#             ${CMAKE_BINARY_DIR}/googletest-build)
#
# # The gtest/gmock targets carry header search path
# # dependencies automatically when using CMake 2.8.11 or
# # later. Otherwise we have to add them here ourselves.
#     if (CMAKE_VERSION VERSION_LESS 2.8.11)
#         include_directories("${gtest_SOURCE_DIR}/include"
#                 "${gmock_SOURCE_DIR}/include")
#     endif()
# endif()

configure_file(game.cmake.in game-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/game-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/game-download )

IF(EXISTS ${CMAKE_BINARY_DIR}/game-src AND EXISTS ${CMAKE_BINARY_DIR}/game-build)

    set(GAME_PUBLIC_DIRS ${CMAKE_BINARY_DIR}/game-src/src/public_include ${CMAKE_BINARY_DIR}/game-src/src/platform/${TARGET_PLATFORM}/public_include)

    list(APPEND TARGET_INCLUDE_DIRS ${GAME_PUBLIC_DIRS})
    list(APPEND TARGET_LIBRARIES game-static)

    add_subdirectory(${CMAKE_BINARY_DIR}/game-src ${CMAKE_BINARY_DIR}/game-build)

endif()

add_subdirectory(src)

