target_sources(${PROJ_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/menu.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/menu_item_group.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/menu_item.cpp
)

add_subdirectory(Menus)