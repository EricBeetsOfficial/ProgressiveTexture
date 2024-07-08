project(Image)

include_directories(.)
include_directories(IO IO/Default/ IO/Dummy/)
include_directories(Process Process/Default/)
include_directories(../Utils)
add_library(Image IO/Default/DefaultImageIO.cpp)
