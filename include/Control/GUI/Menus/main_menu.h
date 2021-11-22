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
		} button_;
	}; // MainMenu class
} // namespace game