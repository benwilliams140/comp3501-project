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
		virtual void HandleInput() override;

	private:
		/*
		Properties related to HUD elements
		All ratios are in reference to the window size
		*/
		const struct HealthBar {
			float widthRatio = 0.2f;
			float heightRatio = 0.025f;
			ImU32 backgroundColor = IM_COL32(255, 0, 0, 255);
			ImU32 foregroundColor = IM_COL32(0, 255, 0, 255);
			ImU32 textColor = IM_COL32(0, 0, 0, 255);
		} healthBar_;

		const struct EnergyBar {
			float widthRatio = 0.02f;
			float heightRatio = 0.2f;
			ImU32 backgroundColor = IM_COL32(160, 160, 160, 255);
			ImU32 foregroundColor = IM_COL32(0, 255, 255, 255);
		} energyBar_;

		const struct ProjectileSelection {
			float widthRatio = 0.15f;
			float heightRatio = 0.025f;
			int inventorySize = 4;
		} projSelection_;

		void RenderHealthBar(Game* game, int windowWidth, int windowHeight);
		void RenderEnergyBar(Game* game, int windowWidth, int windowHeight);
	}; // MainMenu class
} // namespace game