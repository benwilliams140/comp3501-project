add_subdirectory(Hovertank)
add_subdirectory(Projectiles)

target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/terrain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Artifact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EnergySource.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentObject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Rock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Tree.cpp
)