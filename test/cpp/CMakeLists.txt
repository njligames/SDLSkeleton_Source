
if (TARGET ${CMAKE_PROJECT_NAME}-static)
    file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
    file(GLOB HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

    ADD_EXECUTABLE(testStaticLibrary ${SRCS} ${HDRS})

    TARGET_LINK_LIBRARIES(
      testStaticLibrary
      ${CMAKE_PROJECT_NAME}-static
      ${GTEST_LIBRARY}
      ${GMOCK_LIBRARY}
    )

    set_target_properties(testStaticLibrary PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}")

    add_test(NAME testStaticLibrary COMMAND testStaticLibrary)
endif()




