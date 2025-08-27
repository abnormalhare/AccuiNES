cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(AccuiNES LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/msys64/mingw32")

# Gather all .cpp files recursively under src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Place compiled objects in build/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Find GLFW (must be installed or provided via package manager)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Create the executable in the project root (./)
add_executable(AccuiNES ${SOURCES})

# Link GLFW
target_link_libraries(AccuiNES PRIVATE glfw OpenGL::GL)

target_include_directories(AccuiNES PRIVATE src include ${GLFW_INCLUDE_DIRS})

set_target_properties(AccuiNES PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)