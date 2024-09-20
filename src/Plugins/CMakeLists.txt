project(Plugins)

include_directories(.)
include_directories(./Unity ./Export ./Unity/Unity ./Unity/RenderAPI ./Unity/gl3w)
include_directories(../Utils ../Utils/Version ../Utils/Log ../Utils/Pattern ../Utils/Platform ../Utils/Delegate)
include_directories(../Texture)
include_directories(../Worker/Thread ../Worker/Texture ../Worker/Task ../Image ../Image/Process/Splitter)
add_library(Plugins
    ./Export/ExportCommon.cpp
    ./Export/ExportLog.cpp
    ./Export/ExportPlatform.cpp
    ./Export/ExportTexture.cpp
    ./Unity/ProgressiveTexturePlugin.cpp
    ./Unity/RenderAPI/RenderAPI.cpp
    ./Unity/RenderAPI/RenderAPI_D3D11.cpp
    ./Unity/RenderAPI/RenderAPI_D3D12.cpp
    ./Unity/RenderAPI/RenderAPI_OpenGLCoreES.cpp
    ./Unity/RenderAPI/RenderAPI_Vulkan.cpp
)

find_package (OpenGL)
message("Libs: " ${OPENGL_gl_LIBRARY})

add_library(UnityPlugin SHARED
    $<TARGET_OBJECTS:Plugins>
    $<TARGET_OBJECTS:Utils>
    $<TARGET_OBJECTS:Image>
    $<TARGET_OBJECTS:Texture>
    $<TARGET_OBJECTS:Worker>
)

target_link_libraries(UnityPlugin PUBLIC ${OPENGL_gl_LIBRARY})

# install(FILES $<TARGET_RUNTIME_DLLS:UnityPlugin> TYPE BIN)
# install(TARGETS $<TARGET_RUNTIME_DLLS:UnityPlugin> DESTINATION ${INSTALL_FOLDER})
install(TARGETS UnityPlugin DESTINATION ${INSTALL_FOLDER})
