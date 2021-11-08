#include "Control/GUI/menu.h"

namespace game {
	Menu::Menu(GLFWwindow* window) : window(window) {
		
	}

	Menu::~Menu() {

	}

	void Menu::AddVariable(void* var) {
		variables.push_back(var);
	}

	void Menu::HandleInput() {
		// ImGui already handles most input, this is mostly just for specialized additional features
		//		eg. Using the scroll wheel to select items in an HUD element
		// base menu object should not have any additional input (that I can think of)
	}
} // namespace game