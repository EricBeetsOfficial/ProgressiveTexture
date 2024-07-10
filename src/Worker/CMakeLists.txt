project(Worker)

include_directories(. Task
                    ../Utils
                    ../Utils/Log
                    ../Utils/Pattern
                    ../Image
                    ../Image/IO
                    ../Image/IO/Default
                    ../Image/IO/Dummy
                    ../Image/Process/
                    ../Image/Process/Default
                    ../Block
                    Texture
                    Task
                    Thread)
add_library(Worker STATIC Task/ITaskWorker.cpp Texture/TextureTask.cpp)
