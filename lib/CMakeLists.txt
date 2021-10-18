# Require OpenGL library
find_package(OpenGL REQUIRED)
target_include_directories(${PROJ_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

# include all library headers
target_include_directories(${PROJ_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# find libraries
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS lib)
    find_library(GLFW_LIBRARY glfw3 HINTS lib)
    find_library(SOIL_LIBRARY SOIL HINTS lib)
endif(NOT WIN32)

# link libraries
target_link_libraries(${PROJ_NAME} ${OPENGL_gl_LIBRARY})
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
