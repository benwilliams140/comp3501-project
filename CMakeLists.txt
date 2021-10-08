cmake_minimum_required(VERSION 2.6)

# Name of project
set(PROJ_NAME FinalProject)
project(${PROJ_NAME} C CXX)

# Specify project files: header files and source files
set(HDRS
    headers/asteroid.h headers/camera.h headers/game.h headers/model_loader.h headers/resource.h headers/resource_manager.h headers/scene_graph.h headers/scene_node.h
)
 
set(SRCS
   src/asteroid.cpp src/camera.cpp src/game.cpp src/main.cpp src/resource.cpp src/resource_manager.cpp src/scene_graph.cpp src/scene_node.cpp res/shaders/textured_material_fp.glsl res/shaders/textured_material_vp.glsl res/shaders/procedural_vp.glsl res/shaders/procedural_fp.glsl
)


# Add executable based on the source files
add_executable(${PROJ_NAME} ${HDRS} ${SRCS})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH C:/Program\ Files/Libraries/Libraries)
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${PROJ_NAME} ${GLEW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${SOIL_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(${PROJ_NAME} PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
