#pragma once

#include "Control/GUI/menu.h"

namespace game {
	class MainMenu : public Menu {
	public:
		MainMenu();
		~MainMenu();

	private:
		virtual void Init() override;
	}; // Menu class
} // namespace game