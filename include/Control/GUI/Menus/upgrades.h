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
		*/
		struct WeaponUpgrade {
			bool machineGun = false;
			int machineGunCost = 2500;
			bool energyCannon = false;
			int energyCannonCost = 5000;
		} weaponUpgrade_;

		struct SpeedUpgrade {
			int index = 0;
			int cost = 2000;
			float multiplier = 2.0f;
			float increase = 0.25f;
		} speedUpgrade_;

		struct HealthUpgrade {
			int index = 0;
			int cost = 2000;
			float multiplier = 2.0f;
			float increase = 50.0f;
		} healthUpgrade_;

		struct EnergyUpgrade {
			int index = 0;
			int cost = 2000;
			float multiplier = 2.0f;
			float increase = 50.0f;
		} energyUpgrade_;

		const struct Button {
			float widthRatio = 0.15f;
			float heightRatio = 0.075f;
		} button_;

		const struct PointsLabel {
			float widthRatio = 0.15f;
			float heightRatio = 0.075f;
		} pointsLabel_;

		void RenderPoints(int points, ImVec2 windowSize);
		void RenderWeaponUpgrades(int points, ImVec2 buttonSize);
		void RenderSpeedUpgrades(int points, ImVec2 buttonSize);
		void RenderHealthUpgrades(int points, ImVec2 buttonSize);
		void RenderEnergyUpgrades(int points, ImVec2 buttonSize);

		void HandleSpeedUpgradeButtonClick();
		void HandleHealthUpgradeButtonClick();
		void HandleEnergyUpgradeButtonClick();
	}; // MainMenu class
} // namespace game