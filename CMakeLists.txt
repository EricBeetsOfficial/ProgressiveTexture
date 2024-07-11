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
add_subdirectory(src/Block)


include_directories(src/Worker src/Worker/Task src/Worker/Thread src/Worker/Texture)
include_directories(src/Image src/Image/IO src/Image/IO/Default src/Image/IO/Dummy)
include_directories(src/Image/Process src/Image/Process/Resizer src/Image/Process/Splitter)
include_directories(src/Utils src/Utils/Console src/Utils/Log src/Utils/Pattern)

include(CTest)
enable_testing()
add_subdirectory(Test)