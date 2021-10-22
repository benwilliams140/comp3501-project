#include "Control/GUI/menu_item_group.h"

namespace game {
	MenuItemGroup::MenuItemGroup() {

	}

	MenuItemGroup::~MenuItemGroup() {

	}

	void MenuItemGroup::AddChild(Component* c) {
		if (std::find(children.begin(), children.end(), c) != children.end()) {
			children.push_back(c);
		}
	}

	// TODO: update the return value
	bool MenuItemGroup::RemoveChild(Component* c) {
		children.erase(std::remove(children.begin(), children.end(), c), children.end());
		return true;
	}

	void MenuItemGroup::Render() {
		for (auto it = children.begin(); it != children.end(); ++it) {
			(*it)->Render();
		}
	}
} // namespace game