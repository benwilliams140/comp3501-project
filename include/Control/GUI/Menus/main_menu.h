#pragma once

#include <GL/glew.h>
#include "Control/GUI/menu.h"
#include "Control/game.h"

namespace game {
	class MainMenu : public Menu {
	public:
		MainMenu();
		~MainMenu();

		virtual void Render(GLFWwindow* window) override;
	}; // MainMenu class
} // namespace game