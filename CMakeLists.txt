cmake_minimum_required(VERSION 3.13)

# Name of project
set(PROJ_NAME FinalProject)
project(${PROJ_NAME} C CXX)

include_directories(include)

# Add executable based on the source files
add_executable(${PROJ_NAME} src/main.cpp "include/Objects/Hovertank/hovertank.h" "include/Objects/Hovertank/hovertank_track.h" "include/Objects/Hovertank/hovertank_turret.h" "include/Objects/Hovertank/machine_gun.h" "include/Objects/Hovertank/scanner.h"  "include/Control/GUI/menu_item_group.h" "include/Control/GUI/menu_item.h" "include/Control/GUI/Menus/main_menu.h" "include/Control/GUI/component.h" "src/Control/GUI/component.cpp")

add_subdirectory(src)
add_subdirectory(lib)