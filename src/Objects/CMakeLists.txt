add_subdirectory(Hovertank)

target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/asteroid.cpp
)