cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")

project(Accui4004 LANGUAGES CXX)

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

# Create the executable in the project root (./)
add_executable(Accui4004 ${SOURCES})

# Link GLFW
target_link_libraries(Accui4004 PRIVATE glfw)

target_include_directories(Accui4004 PRIVATE src)

set_target_properties(Accui4004 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)