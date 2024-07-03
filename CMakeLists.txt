cmake_minimum_required(VERSION 3.30)

project(Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

## LIBS
# Utils
include_directories(src/Utils)
add_library(Utils STATIC src/Utils/Console.cpp src/Utils/Log.cpp)
# Reader
include_directories(src/Reader src/Reader/Default)
add_library(Reader STATIC src/Reader/IReader.cpp src/Reader/Default/DefaultReader.cpp)
# Worker
include_directories(src/Worker)
add_library(Worker STATIC src/Worker/ThreadWorker.cpp)

## TESTS
# Reader
add_executable(ReaderTexture Test/reader.cpp)
target_link_libraries(ReaderTexture Reader Utils)
# Threads
add_executable(Thread Test/thread.cpp)
target_link_libraries(Thread Worker Utils Reader)
# Templates
# add_executable(Templates Test/templates.cpp)
# target_link_libraries(Templates Utils)

# ## UNIT TESTS
include(CTest)
# set(CTEST_MEMORYCHECK_TYPE "AddressSanitizer")
# set(CTEST_MEMORYCHECK_SANITIZER_OPTIONS "verbosity=1:symbolize=1:abort_on_error=1:detect_leaks=1")

enable_testing()
add_subdirectory(Test)