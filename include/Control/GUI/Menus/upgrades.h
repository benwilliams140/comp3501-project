#pragma once

#include "Control/GUI/menu.h"

namespace game {
	class Game; // forward declaration of Game class

	class Upgrades : public Menu {
	public:
		Upgrades();
		~Upgrades();

		virtual void Render() override;

	private:
		/*
		Properties related to upgrade elements
		All ratios are in reference to the window size
		*/
		struct UpgradeIndices {
			int speed = 0;
			int health = 0;
			int energy = 0;
			bool machineGun = false;
			bool energyCannon = false;
		} upgradeIndices_;

		const struct Button {
			float widthRatio = 0.15f;
			float heightRatio = 0.075f;
		} button_;
		/*
		const struct HealthBar {
			float widthRatio = 0.2f;
			float heightRatio = 0.05f;
			ImTextureID backgroundImage = Menu::LoadImage("health_bar_background.png");
			ImU32 foregroundColor = IM_COL32(0, 200, 0, 255);
		} healthBar_;*/

		void RenderWeaponUpgrades(int points, ImVec2 buttonSize);
		void RenderSpeedUpgrades(int points, ImVec2 buttonSize);
		void RenderHealthUpgrades(int points, ImVec2 buttonSize);
		void RenderEnergyUpgrades(int points, ImVec2 buttonSize);
	}; // MainMenu class
} // namespace game