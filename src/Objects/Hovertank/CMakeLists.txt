add_subdirectory(Abilities)

target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/hovertank.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/hovertank_track.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/hovertank_turret.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp
)