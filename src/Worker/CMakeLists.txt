project(Worker)

include_directories(.)
add_library(Worker STATIC ThreadWorker.cpp)
