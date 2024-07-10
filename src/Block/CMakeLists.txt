project(Block)

include_directories(.)
include_directories(../Utils ../Utils/Log ../Utils/Pattern)
add_library(Block Block.cpp)