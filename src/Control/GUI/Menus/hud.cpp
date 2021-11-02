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

		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize;

		ImGui::Begin("Main Menu", (bool*)true, flags);

		// calculate health bar position and size
		float health = game->GetPlayer()->GetHealth();
		float healthBarBaseWidth = windowWidth * healthBar_.widthRatio;
		float healthBarBaseHeight = windowHeight * healthBar_.heightRatio;
		float healthBarBaseX = windowWidth / 2 - healthBarBaseWidth / 2;
		float healthBarBaseY = 5;
		float healthBarWidth = (healthBarBaseWidth - 4) * health / game->GetPlayer()->GetMaxHealth();
		float healthBarX = healthBarBaseX + 2;
		float healthBarY = healthBarBaseY + 2;

		// render the health bar (can replace the base colour with an image)
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(healthBarBaseX, healthBarBaseY), ImVec2(healthBarBaseX + healthBarBaseWidth, healthBarBaseY + healthBarBaseHeight), IM_COL32(255, 0, 0, 255), 0.0f, 0);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(healthBarX, healthBarY), ImVec2(healthBarX + healthBarWidth, healthBarY + healthBarBaseHeight - 4), IM_COL32(0, 255, 0, 255), 0.0f, 0);
		ImGui::GetWindowDrawList()->AddText(ImVec2(healthBarBaseX + healthBarBaseWidth / 2 - 10, healthBarBaseY + healthBarBaseHeight / 2 - 8), IM_COL32(0, 0, 0, 255), std::to_string((int) health).c_str());

		// render a second option for a health bar using the slider widget
		ImGui::PushItemWidth(healthBarWidth);
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - healthBarWidth / 2, healthBarY + healthBarBaseHeight + 5));
		ImGui::BeginDisabled();
		ImGui::SliderFloat("", &health, 0, game->GetPlayer()->GetMaxHealth(), "%.2f", 0);
		ImGui::EndDisabled();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game