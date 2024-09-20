cmake_minimum_required(VERSION 3.30)
project(UnitTest)

# Setup GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Build function
function(BuildTest AppName sources libs)
  message(${AppName})
  message("${sources}")
  add_executable(${AppName} "${sources}")
  target_link_libraries(${AppName} GTest::gtest_main "${libs}")
  add_test(${AppName} ${AppName})
  include(GoogleTest)
  gtest_discover_tests(${AppName})
endfunction()

set(SOURCES_LIST templates.cpp)
set(LIBS_LIST Utils)
BuildTest(TestTemplates "${SOURCES_LIST}" "${LIBS_LIST}")

set(SOURCES_LIST hello_test.cpp)
BuildTest(TestHello "${SOURCES_LIST}" "${LIBS_LIST}")

set(SOURCES_LIST utils.cpp)
BuildTest(TestUtils "${SOURCES_LIST}" "${LIBS_LIST}")

add_executable(ImageTest images.cpp)
target_link_libraries(ImageTest Utils Image)

find_package (OpenGL)
message("Libs: " ${OPENGL_gl_LIBRARY})

add_executable(ThreadTest thread.cpp)
target_link_libraries(ThreadTest Utils Image Texture Worker ${OPENGL_gl_LIBRARY})