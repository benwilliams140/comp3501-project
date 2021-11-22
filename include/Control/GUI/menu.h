#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#define BUTTON_COLOR ImVec4(1, 1, 1, 1)
#define BUTTON_HOVERED_COLOR ImVec4(0.95, 0.95, 0.95, 1)
#define BUTTON_ACTIVE_COLOR ImVec4(0.4, 0.4, 1, 1)
#define TEXT_COLOR ImVec4(0, 0, 0, 1)

namespace game {
	// add any new menu types here (maybe an inventory, artifact screen, shop, etc.)
	enum class MenuType {
		MAIN,
		PAUSE,
		HUD,
		UPGRADES
	};

	class Menu {
	public:
		Menu();
		~Menu();

		void AddVariable(void* var);

		// overridden by specialized Menu classes (eg. MainMenu)
		virtual void Render() = 0; // handles rendering ImGui widgets (no base implementation)
		virtual void HandleInput(); // handles any additional input for menus

		// loads an image using SOIL for use in one of the GUIs
		static ImTextureID LoadImage(std::string filename);

	protected:
		int initialWindowWidth, initialWindowHeight;
		std::vector<void*> variables; // not currently used - idea is to store menu-specific variables
										// that will be edited by ImGui widgets (eg. the FOV in the pause menu)
	}; // Menu class
} // namespace game