#pragma once

#include "Control/GUI/menu.h"
#include "Control/game.h"

namespace game {
	class Game; // forward declaration of Game class

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
			float widthRatio = 0.025f;
			float heightRatio = 0.2f;
		} energyBar_;

		void RenderHealthBar(Game* game, int windowWidth, int windowHeight);
		void RenderEnergyBar(Game* game, int windowWidth, int windowHeight);
	}; // MainMenu class
} // namespace game