file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testStaticLibrary ${SRCS})

TARGET_LINK_LIBRARIES(
  testStaticLibrary
  ${CMAKE_PROJECT_NAME}-static
  ${GTEST_LIBRARY}
  ${GMOCK_LIBRARY}
)

add_test(NAME testStaticLibrary
         COMMAND testStaticLibrary)

