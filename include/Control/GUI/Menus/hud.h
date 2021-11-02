#pragma once

#include "Control/GUI/menu.h"
#include "Control/game.h"

namespace game {
	class HUD : public Menu {
	public:
		HUD(GLFWwindow* window);
		~HUD();

		virtual void Render() override;

	private:
		/*
		Properties related to HUD elements
		All ratios are in reference to the window size
		*/
		const struct HealthBar {
			float widthRatio = 0.2f;
			float heightRatio = 0.025f;
		} healthBar_;

		const struct EnergyBar {
			float widthRatio = 0.05f;
		} energyBar_;
	}; // MainMenu class
} // namespace game