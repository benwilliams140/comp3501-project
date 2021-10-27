add_subdirectory(Hovertank)

target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/terrain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Artifact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
)