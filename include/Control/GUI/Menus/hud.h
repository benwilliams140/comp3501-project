#pragma once

#include "Control/GUI/menu.h"
#include "Objects/Hovertank/Abilities/ability.h"

namespace game {
	class Game; // forward declaration of Game class

	class HUD : public Menu {
	public:
		HUD();
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
			ImTextureID backgroundImage = Menu::LoadImage("energy_bar_background.png");
			ImU32 foregroundColor = IM_COL32(0, 255, 0, 255);
			ImU32 textColor = IM_COL32(0, 0, 0, 255);
		} healthBar_;

		const struct EnergyBar {
			float widthRatio = 0.02f;
			float heightRatio = 0.2f;
			ImU32 backgroundColor = IM_COL32(160, 160, 160, 155);
			ImU32 foregroundColor = IM_COL32(0, 255, 255, 255);
		} energyBar_;

		const struct ProjectileSelection {
			float widthRatio = 0.15f;
			float heightRatio = 0.05f;
			ImU32 backgroundColor = IM_COL32(100, 100, 100, 155);
			ImU32 abilityColor = IM_COL32(160, 160, 160, 255);
			ImU32 cooldownColor = IM_COL32(140, 140, 140, 255);
			ImU32 selectedColor = IM_COL32(255, 255, 255, 255);
		} projSelection_;

		void RenderHealthBar(int windowWidth, int windowHeight);
		void RenderEnergyBar(int windowWidth, int windowHeight);
		void RenderProjectileSelection(int windowWidth, int windowHeight);
	}; // MainMenu class
} // namespace game