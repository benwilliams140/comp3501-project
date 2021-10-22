add_subdirectory(GUI)

target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource_manager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene_graph.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene_node.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
)