cmake_minimum_required(VERSION 3.16)
project(blackjack VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(builddir "${CMAKE_SOURCE_DIR}/build")
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${builddir}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${builddir}")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/Classes/*.cpp"
)

add_library(imgui
    vendored/imgui/imgui.cpp
    vendored/imgui/imgui_demo.cpp
    vendored/imgui/imgui_draw.cpp
    vendored/imgui/imgui_tables.cpp
    vendored/imgui/imgui_widgets.cpp
    vendored/imgui/backends/imgui_impl_sdl3.cpp
    vendored/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include header directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Classes
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    vendored/SDL/include          # SDL headers
    vendored/imgui               # ImGui headers (imgui.h is here)
    vendored/imgui/backends      # ImGui backends
)

target_include_directories(imgui PRIVATE
    vendored/imgui
    vendored/imgui/backends
    vendored/SDL/include
)

# Link SDL3 to imgui
target_link_libraries(imgui PRIVATE SDL3::SDL3)

# Link executable to imgui and SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE imgui SDL3::SDL3)
