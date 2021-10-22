#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Control/GUI/component.h"

namespace game {
	class MenuItemGroup : public Component {
	public:
		MenuItemGroup();
		~MenuItemGroup();

		void AddChild(Component* c);
		bool RemoveChild(Component* c);

		virtual void Render() override;

	private:
		std::vector<Component*> children;
	}; // Component class
} // namespace game