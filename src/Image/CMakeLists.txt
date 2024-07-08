project(ImageIO)

include_directories(. ./Default/ ./Dummy/)
include_directories(../Utils)
add_library(ImageIO STATIC IImageIO.cpp Default/DefaultImageIO.cpp)
