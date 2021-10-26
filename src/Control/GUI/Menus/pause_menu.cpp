#include "Control/GUI/Menus/pause_menu.h"

namespace game {
	PauseMenu::PauseMenu(GLFWwindow* window) : Menu(window) {
		
	}

	PauseMenu::~PauseMenu() {

	}

	void PauseMenu::Render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags flags = 0;
		flags |= ImGuiWindowFlags_NoTitleBar;
		flags |= ImGuiWindowFlags_NoBackground;
		flags |= ImGuiWindowFlags_NoResize;
		ImGui::Begin("Pause Menu", (bool*)true, flags);
		if (ImGui::Button("Quit")) {
			glfwSetWindowShouldClose(window_, GL_TRUE);
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game