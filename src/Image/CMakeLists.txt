project(Image)

include_directories(.)
include_directories(IO IO/Default/ IO/Dummy/)
include_directories(Process Process/Resizer/ Process/Splitter/ Process/Flipper/)
include_directories(../Utils ../Utils/Log ../Utils/Pattern)
add_library(Image
            Image.cpp
            IO/Default/DefaultImageIO.cpp
            Process/Resizer/ResizerImageProcess.cpp
            Process/Flipper/FlipperImageProcess.cpp
            Process/Splitter/SplitterImageProcess.cpp
            Process/Splitter/Block.cpp)
