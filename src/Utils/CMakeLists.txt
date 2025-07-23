project(Utils)

include_directories(. Console Delegate Log Platform Platform/gl3w)
add_library(Utils STATIC Console/Console.cpp Log/Log.cpp Platform/gl3w/gl3w.c Platform/gl3w/gl3w.h Platform/gl3w/glcorearb.h)