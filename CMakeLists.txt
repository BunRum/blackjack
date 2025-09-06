cmake_minimum_required(VERSION 3.10)
project(blackjack VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/Classes/*.cpp"  # include all cpp files in the classes folder
)
# message(STATUS "Sources: ${SOURCES}")
# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include header directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Classes
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Find SDL3
find_package(SDL3 CONFIG REQUIRED PATHS "${CMAKE_SOURCE_DIR}/external/SDL3/lib/cmake/SDL3")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Use SDL main callbacks
target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_USE_CALLBACKS)

# Optional: static linking and stdc++ experimental lib if needed
# target_link_options(${PROJECT_NAME} PRIVATE -static)
# target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)
