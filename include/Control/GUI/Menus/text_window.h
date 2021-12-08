#pragma once

#include <unordered_map>

#include "Control/GUI/menu.h"

namespace game {
	enum class TextState {
		NOTHING,
		WELCOME,
		CONTROLS
	};

	class TextWindow : public Menu {
	public:
		TextWindow();
		~TextWindow();

		virtual void Render() override;
		
		void AddState(TextState state);
		TextState GetState();

	private:
		ImFont* font = Menu::LoadFont("FabulaValhalla.ttf", 13.5f);
		std::unordered_map<TextState, bool> previouslySeen_;
		std::vector<TextState> stateQueue_;

		void RenderWelcomeText();
		void RenderControlText();
	}; // PauseMenu class
} // namespace game