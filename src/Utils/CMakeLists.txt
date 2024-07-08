project(Utils)

include_directories(.)
add_library(Utils STATIC Console.cpp Log.cpp)
