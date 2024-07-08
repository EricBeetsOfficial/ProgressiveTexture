project(Image)

include_directories(IO IO/Default/ IO/Dummy/)
include_directories(../Utils)
add_library(Image STATIC IO/IImageIO.cpp IO/Default/DefaultImageIO.cpp)
