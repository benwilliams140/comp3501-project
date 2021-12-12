cmake_minimum_required(VERSION 3.13)

# Name of project
set(PROJ_NAME FinalProject)
project(${PROJ_NAME} C CXX)

# Set include directory
include_directories(include)

# Add executable based on the source files
add_executable(${PROJ_NAME} src/main.cpp "include/Control/GUI/Menus/you_win.h" "src/Control/GUI/Menus/you_win.cpp")


# Add src and lib subdirectories
add_subdirectory(src)
add_subdirectory(lib)
