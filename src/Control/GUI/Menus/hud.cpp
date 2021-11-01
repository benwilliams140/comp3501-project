#include "Control/GUI/Menus/hud.h"

namespace game {
	HUD::HUD(GLFWwindow* window) : Menu(window) {

	}

	HUD::~HUD() {

	}

	void HUD::Render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		void* ptr = glfwGetWindowUserPointer(window);
		Game* game = (Game*)ptr;

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize;

		ImGui::Begin("Main Menu", (bool*)true, flags);

		//ImGui::SetNextWindowSize(ImVec2())
		//ImGui::SetNextWindowPos();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game