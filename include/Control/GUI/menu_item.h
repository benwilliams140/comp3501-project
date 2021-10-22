#pragma once

#include <string>

#include "Control/GUI/component.h"

namespace game {
	class MenuItem : public Component {
	public:
		MenuItem();
		~MenuItem();

		virtual void Render() override;
	}; // Component class
} // namespace game