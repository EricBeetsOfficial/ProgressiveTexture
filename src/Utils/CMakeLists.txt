project(Utils)

include_directories(. Console Log)
add_library(Utils STATIC Console/Console.cpp Log/Log.cpp)
