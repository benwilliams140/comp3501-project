#pragma once

#include "Control/GUI/menu.h"

namespace game {
	class PauseMenu : public Menu {
	public:
		PauseMenu(GLFWwindow* window);
		~PauseMenu();
		
		virtual void Render() override;
	}; // PauseMenu class
} // namespace game