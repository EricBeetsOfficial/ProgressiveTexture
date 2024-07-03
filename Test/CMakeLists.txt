cmake_minimum_required(VERSION 3.30)
project(UnitTest)

message("TEST PROJECT")

# Setup GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test cpp file
add_executable(HelloTest hello_test.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(HelloTest GTest::gtest_main)

add_test(HelloTest HelloTest)

include(GoogleTest)
gtest_discover_tests(HelloTest)


add_executable(TemplatesTest templates.cpp)
target_link_libraries(TemplatesTest GTest::gtest_main Utils)
add_test(TemplatesTest TemplatesTest)
include(GoogleTest)
gtest_discover_tests(TemplatesTest)