cmake_minimum_required(VERSION 3.13)

# Name of project
set(PROJ_NAME FinalProject)
project(${PROJ_NAME} C CXX)

include_directories(include)

# Add executable based on the source files
add_executable(${PROJ_NAME} src/main.cpp "src/Objects/terrain.cpp" "include/Objects/terrain.h")

add_subdirectory(src)
add_subdirectory(lib)