#include "Control/GUI/menu.h"

namespace game {
	Menu::Menu() {
		
	}

	Menu::~Menu() {

	}

	void Menu::addVariable(void* var) {
		variables.push_back(var);
	}
} // namespace game