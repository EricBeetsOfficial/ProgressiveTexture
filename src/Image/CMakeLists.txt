project(Image)

include_directories(.)
include_directories(IO IO/Default/ IO/Dummy/)
include_directories(Process Process/Default/ Process/Splitter/)
include_directories(../Utils ../Utils/Log ../Utils/Pattern)
add_library(Image Image.cpp IO/Default/DefaultImageIO.cpp Process/Default/DefaultImageProcess.cpp Process/Splitter/SplitterImageProcess.cpp)
