#pragma once

#include "Control/GUI/menu.h"
#include "Control/game.h"

namespace game {
	class HUD : public Menu {
	public:
		HUD(GLFWwindow* window);
		~HUD();

		virtual void Render() override;
	}; // MainMenu class
} // namespace game