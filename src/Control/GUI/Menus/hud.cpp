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
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin("HUD", (bool*)true, flags);

		RenderHealthBar(game, windowWidth, windowHeight);
		RenderEnergyBar(game, windowWidth, windowHeight);

		// render the energy bar (can replace the base colour with an image)

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void HUD::RenderHealthBar(Game* game, int windowWidth, int windowHeight) {
		// calculate health bar position and size
		float health = game->GetPlayer()->GetHealth();
		// outer rectangle
		float healthBarBaseWidth = windowWidth * healthBar_.widthRatio;
		float healthBarBaseHeight = windowHeight * healthBar_.heightRatio;
		float healthBarBaseX = windowWidth / 2 - healthBarBaseWidth / 2;
		float healthBarBaseY = 5;
		// inner rectangle
		float healthBarWidth = (healthBarBaseWidth - 4.0f) * health / game->GetPlayer()->GetMaxHealth();
		float healthBarHeight = healthBarBaseHeight - 4.0f;
		float healthBarX = healthBarBaseX + 2.0f;
		float healthBarY = healthBarBaseY + 2.0f;

		// render the health bar (can replace the base colour with an image)
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(healthBarBaseX, healthBarBaseY), ImVec2(healthBarBaseX + healthBarBaseWidth, healthBarBaseY + healthBarBaseHeight), IM_COL32(255, 0, 0, 255), 0.0f, 0);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(healthBarX, healthBarY), ImVec2(healthBarX + healthBarWidth, healthBarY + healthBarHeight), IM_COL32(0, 255, 0, 255), 0.0f, 0);
		ImGui::GetWindowDrawList()->AddText(ImVec2(healthBarBaseX + healthBarBaseWidth / 2 - 10, healthBarBaseY + healthBarBaseHeight / 2 - 8), IM_COL32(0, 0, 0, 255), std::to_string((int)health).c_str());

		// render a second option for a health bar using the slider widget
		ImGui::PushItemWidth(healthBarBaseWidth);
		ImGui::SetCursorPos(ImVec2(healthBarBaseX, healthBarY + healthBarBaseHeight + 5));
		ImGui::BeginDisabled();
		ImGui::SliderFloat("", &health, 0, game->GetPlayer()->GetMaxHealth(), "%.2f", 0);
		ImGui::EndDisabled();
	}

	void HUD::RenderEnergyBar(Game* game, int windowWidth, int windowHeight) {
		// calculate energy bar positions and sizes
		float energy = game->GetPlayer()->GetEnergy();
		// outer rectangle
		float energyBarBaseWidth = windowWidth * energyBar_.widthRatio;
		float energyBarBaseHeight = windowHeight * energyBar_.heightRatio;
		float energyBarBaseX = windowWidth - energyBarBaseWidth - 2.0f;
		float energyBarBaseY = windowHeight - energyBarBaseHeight - 2.0f;
		// inner rectangle
		float energyBarWidth = energyBarBaseWidth - 6.0f;
		float energyBarHeight = (energyBarBaseHeight - 4.0f) * energy / game->GetPlayer()->GetMaxEnergy();
		float energyBarX = energyBarBaseX + 2.0f;
		float energyBarY = energyBarBaseY + energyBarBaseHeight - 2.0f - energyBarHeight;

		// render the energy bar (can replace the base colour with an image)
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(energyBarBaseX, energyBarBaseY), ImVec2(energyBarBaseX + energyBarBaseWidth, energyBarBaseY + energyBarBaseHeight), IM_COL32(255, 0, 0, 255), 0.0f, 0);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(energyBarX, energyBarY), ImVec2(energyBarX + energyBarWidth, energyBarY + energyBarHeight), IM_COL32(0, 255, 255, 255), 0.0f, 0);
		
		// render a second option for an energy bar using the slider widget
		ImGui::SetCursorPos(ImVec2(energyBarBaseX - energyBarBaseWidth - 5, energyBarBaseY));
		ImGui::BeginDisabled();
		ImGui::VSliderFloat("", ImVec2(energyBarBaseWidth, energyBarBaseHeight), &energy, 0, game->GetPlayer()->GetMaxEnergy(), "%.2f", 0);
		ImGui::EndDisabled();
	}
} // namespace game