project(Worker)

include_directories(.)
add_library(Worker STATIC ThreadPool.cpp ThreadWorker.cpp)
