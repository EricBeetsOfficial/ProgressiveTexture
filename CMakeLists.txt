cmake_minimum_required(VERSION 3.30)

project(Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/libs)

add_subdirectory(src/Utils)
add_subdirectory(src/Image)
add_subdirectory(src/Worker)


include_directories(src/Worker)
include_directories(src/Image src/Image/IO src/Image/IO/Default src/Image/IO/Dummy)
include_directories(src/Image/Process src/Image/Process/Default)
include_directories(src/Utils)

include(CTest)
enable_testing()
add_subdirectory(Test)