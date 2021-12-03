add_subdirectory(Hovertank)
add_subdirectory(Projectiles)
add_subdirectory(Hazards)

target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/terrain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Artifact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EnergySource.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentObject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Rock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Tree.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Enemy.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ShooterEnemy.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/CarePackage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Particle.cpp
)