project(Worker)

include_directories(. Task
                    ../Utils
                    ../Utils/Log
                    ../Utils/Pattern
                    ../Image
                    ../Image/IO
                    ../Image/IO/Default
                    ../Image/IO/Dummy
                    ../Image/Process/Resizer
                    ../Image/Process/Splitter
                    ../Image/Process/
                    ../Block
                    Texture
                    Task
                    Thread)
add_library(Worker STATIC Task/ITaskWorker.cpp Texture/TextureTask.cpp)
