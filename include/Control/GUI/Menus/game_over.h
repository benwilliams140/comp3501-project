#pragma once

#include "Control/GUI/menu.h"

namespace game {
class GameOver : public Menu {
public:
	GameOver();
	~GameOver();

	virtual void Render() override;

private:
	const struct Button {
		float widthRatio = 0.15f;
		float heightRatio = 0.075f;
		ImTextureID quitImage = Menu::LoadImage("button.png");
	} button_;

	const struct Background {
		ImTextureID image = Menu::LoadImage("game_over.png");
	} background_;

	void RenderQuitButton(ImVec2 windowSize, ImVec2 buttonSize);
	void RenderBackground(ImVec2 windowSize);
};
} // namespace game