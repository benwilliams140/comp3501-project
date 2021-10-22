#pragma once

#include <nanogui/nanogui.h>

#include "Control/GUI/menu_item_group.h"

namespace game {
	class Menu {
	public:
		Menu();
		~Menu();

		void Render();

	protected:
		MenuItemGroup* base;

	private:
		virtual void Init() = 0;
	}; // Menu class
} // namespace game