cmake_minimum_required(VERSION 3.30)
project(SDL_SAMPLE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.20
)
FetchContent_MakeAvailable(SDL3)

function(CompileSample list_files definition list_libs)
    include_directories(.)
    add_executable(${PROJECT_NAME} ../sample.cpp ../sample_sdl.cpp ${list_files})
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${definition})
    target_link_libraries(${PROJECT_NAME} ${list_libs})

endfunction()

add_subdirectory(./OGL)
add_subdirectory(./DX11)
