#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace game {
	// add any new menu types here (maybe an inventory, artifact screen, shop, etc.)
	enum class MenuType {
		MAIN,
		PAUSE,
		HUD,
		UPGRADES,
		GAME_OVER
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
		static ImFont* LoadFont(std::string filename, float size);

	protected:
		int initialWindowWidth, initialWindowHeight;
		std::vector<void*> variables; // not currently used - idea is to store menu-specific variables
										// that will be edited by ImGui widgets (eg. the FOV in the pause menu)
	}; // Menu class
} // namespace game