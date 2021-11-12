#pragma once

#include "Control/GUI/menu.h"

namespace game {
	class MainMenu : public Menu {
	public:
		MainMenu();
		~MainMenu();

		virtual void Render() override;
	}; // MainMenu class
} // namespace game