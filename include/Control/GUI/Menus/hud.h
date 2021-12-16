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

		void ActivateTooltip(std::string text, float time);
		void DeactivateTooltip();

		void StartInjuredEffect();

	private:
		/*
		Properties related to HUD elements
		All ratios are in reference to the window size
		*/
		struct InformationBar {
			bool active = false;
			std::string text = "";
			float lifespan = 0.0f;
			ImFont* font = Menu::LoadFont("FabulaValhalla.ttf", 16.0f);
		} infoBar_;

		struct ArtifactBar {
			std::string text;
			ImFont* font = Menu::LoadFont("FabulaValhalla.ttf", 18.0f);
		} artifactBar_;

		const struct HealthBar {
			float widthRatio = 0.2f;
			float heightRatio = 0.05f;
			ImTextureID backgroundImage = Menu::LoadImage("health_bar_background.png");
			ImU32 foregroundColor = IM_COL32(0, 200, 0, 255);
		} healthBar_;

		const struct EnergyBar {
			float widthRatio = 0.045f;
			float heightRatio = 0.25f;
			ImTextureID backgroundImage = Menu::LoadImage("energy_bar_background.png");
			ImU32 foregroundColor = IM_COL32(0, 255, 255, 255);
		} energyBar_;

		const struct ProjectileSelection {
			float widthRatio = 0.15f;
			float heightRatio = 0.05f;
			ImU32 backgroundColor = IM_COL32(100, 100, 100, 155);
			ImU32 abilityColor = IM_COL32(160, 160, 160, 255);
			ImU32 cooldownColor = IM_COL32(140, 140, 140, 200);
			ImU32 selectedColor = IM_COL32(255, 255, 255, 255);
		} projSelection_;

		void RenderInformationBar(ImVec2 windowSize, ImVec2 windowRatio);
		void RenderArtifactBar();
		void RenderHealthBar(ImVec2 windowSize, ImVec2 windowRatio);
		void RenderEnergyBar(ImVec2 windowSize, ImVec2 windowRatio);
		void RenderProjectileSelection(ImVec2 windowSize, ImVec2 windowRatio);
	}; // MainMenu class
} // namespace game