#pragma once

#include <string>

namespace game {
	class Component {
	public:
		Component();
		~Component();

		virtual void Render() = 0;

	private:

	}; // Component class
} // namespace game