#pragma once

#include <iostream>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace game {
	enum class MenuType {
		MAIN,
		PAUSE,
		HUD
	};

	class Menu {
	public:
		Menu(GLFWwindow* window);
		~Menu();

		virtual void Render() = 0;

	protected:
		GLFWwindow* window_;
	}; // Menu class
} // namespace game