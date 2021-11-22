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
	} button_;
	}; // PauseMenu class
} // namespace game