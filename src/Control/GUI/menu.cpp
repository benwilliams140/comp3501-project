#include "Control/GUI/menu.h"

namespace game {
	Menu::Menu() {
		base = new MenuItemGroup();
	}

	Menu::~Menu() {

	}

	void Menu::Render() {
		base->Render();
	}
} // namespace game