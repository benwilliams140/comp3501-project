#pragma once

#include "Control/GUI/menu.h"
#include "Control/game.h"

namespace game {
	class MainMenu : public Menu {
	public:
		MainMenu(GLFWwindow* window);
		~MainMenu();

		virtual void Render() override;
	}; // MainMenu class
} // namespace game