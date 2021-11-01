#include "Control/GUI/menu.h"

namespace game {
	Menu::Menu(GLFWwindow* window) : window(window) {
		glfwGetWindowSize(window, &initialWindowWidth, &initialWindowHeight);
	}

	Menu::~Menu() {

	}

	void Menu::AddVariable(void* var) {
		variables.push_back(var);
	}
} // namespace game