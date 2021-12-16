#pragma once

#include "Control/GUI/menu.h"

namespace game {
	class MainMenu : public Menu {
	public:
		MainMenu();
		~MainMenu();

		virtual void Render() override;

	private:
		const struct Button {
			float widthRatio = 0.15f;
			float heightRatio = 0.075f;
			// need different textures so the buttons will have different IDs
			// it's an old API... we can implement our own button click handler to avoid this
			// or figure out how to properly use PushID/PopID (from what I saw it doesn't work
			//		with ImageButton, there could've been an update though)
			ImTextureID quitImage = Menu::LoadImage("button.png");
			ImTextureID startImage = Menu::LoadImage("button.png");
			ImFont* font = Menu::LoadFont("Freedom.ttf", 14.0f);
			ImVec4 textColor = ImVec4(1, 1, 1, 1);
		} button_;

		const struct Background {
			ImTextureID image = Menu::LoadImage("title_screen.png");
		} background_;

		const struct TitleBar {
			std::string title = "Planet Explorer";
			ImFont* font = Menu::LoadFont("Freedom.ttf", 54.0f);
			ImVec4 textColor = ImVec4(1, 1, 1, 1);
		} titleBar_;

		void RenderStartButton(ImVec2 windowSize, ImVec2 buttonSize);
		void RenderQuitButton(ImVec2 windowSize, ImVec2 buttonSize);
		void RenderBackground(ImVec2 windowSize);
		void RenderTitle(ImVec2 windowSize);
	}; // MainMenu class
} // namespace game