#pragma once

#include <GL/glew.h>
#include "Control/GUI/menu.h"
#include "Control/game.h"

namespace game {
	class PauseMenu : public Menu {
	public:
		PauseMenu();
		~PauseMenu();
		
		virtual void Render(GLFWwindow* window) override;
	}; // PauseMenu class
} // namespace game