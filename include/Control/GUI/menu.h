#pragma once

#include <iostream>
#include <vector>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 150
#define BUTTON_COLOR ImVec4(1, 1, 1, 1)
#define BUTTON_HOVERED_COLOR ImVec4(0.95, 0.95, 0.95, 1)
#define BUTTON_ACTIVE_COLOR ImVec4(0.4, 0.4, 1, 1)
#define TEXT_COLOR ImVec4(0, 0, 0, 1)

namespace game {
	enum class MenuType {
		MAIN,
		PAUSE,
		HUD
	};

	class Menu {
	public:
		Menu();
		~Menu();

		void addVariable(void* var);

		virtual void Render(GLFWwindow* window) = 0;

	protected:
		std::vector<void*> variables;
	}; // Menu class
} // namespace game