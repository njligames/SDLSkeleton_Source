
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
