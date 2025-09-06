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

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include header directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Classes
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Find SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Use SDL main callbacks
# target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_USE_CALLBACKS)
