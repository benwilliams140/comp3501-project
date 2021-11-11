cmake_minimum_required(VERSION 3.13)

# Name of project
set(PROJ_NAME FinalProject)
project(${PROJ_NAME} C CXX)

# Set include directory
include_directories(include)

# Add executable based on the source files
add_executable(${PROJ_NAME} src/main.cpp "include/Objects/Rock.h" "src/Objects/Rock.cpp" "include/Objects/Tree.h" "src/Objects/Tree.cpp" "include/Objects/EnergySource.h" "src/Objects/EnergySource.cpp")

# Add src and lib subdirectories
add_subdirectory(src)
add_subdirectory(lib)
