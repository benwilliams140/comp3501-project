#pragma once

#include "Control/GUI/menu.h"

namespace game {
	class PauseMenu : public Menu {
	public:
		PauseMenu();
		~PauseMenu();
		
		virtual void Render() override;

	private:
		const struct Button {
			float widthRatio = 0.15f;
			float heightRatio = 0.075f;
			// need different texture IDs so the buttons have different IDs
			ImTextureID quitImage = Menu::LoadImage("button.png");
			ImTextureID resumeImage = Menu::LoadImage("button.png");
			ImTextureID settingsImage = Menu::LoadImage("button.png");
			ImFont* font = Menu::LoadFont("Freedom.ttf", 14.0f);
			ImVec4 textColor = ImVec4(1, 1, 1, 1);
		} button_;

		void RenderQuitButton(ImVec2 windowSize, ImVec2 buttonSize);
		void RenderSettingsButton(ImVec2 windowSize, ImVec2 buttonSize);
		void RenderResumeButton(ImVec2 windowSize, ImVec2 buttonSize);
	}; // PauseMenu class
} // namespace game