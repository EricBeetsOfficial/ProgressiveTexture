cmake_minimum_required(VERSION 3.30)

project(Test)

# set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/libs)
set(INSTALL_FOLDER "C:/Users/eric_/Programming/Git/UnityProgressiveTexture/Assets/Plugins/Windows")

message("Build:  " ${CMAKE_BUILD_TYPE})
message("Output: " ${CMAKE_BINARY_DIR}/../output/)
message("Output: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("Install to: " ${INSTALL_FOLDER})

add_definitions(-DUSE_OPENGL)
add_definitions(-DUSE_VULKAN=0)
add_definitions(-DUSE_D3D=0)

# add_definitions(-DTARGET_OS_WSA)

add_subdirectory(src/Utils)
add_subdirectory(src/Image)
add_subdirectory(src/Texture)
add_subdirectory(src/Worker)
add_subdirectory(src/Plugins)

include_directories(src/Worker src/Worker/Task src/Worker/Thread src/Worker/Texture)
include_directories(src/Image src/Image/IO src/Image/IO/Default src/Image/IO/Dummy)
include_directories(src/Image/Process src/Image/Process/Resizer src/Image/Process/Splitter)
include_directories(src/Texture)
include_directories(src/Utils src/Utils/Console src/Utils/Log src/Utils/Pattern)

include(CTest)
enable_testing()
add_subdirectory(Test)