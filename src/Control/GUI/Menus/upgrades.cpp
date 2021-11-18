#include "Control/GUI/Menus/upgrades.h"
#include "Control/game.h"

namespace game {
	Upgrades::Upgrades()
	{
	}

	Upgrades::~Upgrades()
	{
	}

	void Upgrades::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int windowWidth, windowHeight;
		glfwGetWindowSize(Game::GetInstance().GetWindow(), &windowWidth, &windowHeight);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin("Upgrades", (bool*)true, flags);

		// renders the players points
		int points = Game::GetInstance().GetPlayer()->GetMoney();
		ImVec2 buttonSize = ImVec2(windowWidth * button_.widthRatio, windowHeight * button_.heightRatio);

		RenderWeaponUpgrades(points, buttonSize);
		RenderSpeedUpgrades(points, buttonSize);
		RenderHealthUpgrades(points, buttonSize);
		RenderEnergyUpgrades(points, buttonSize);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Upgrades::RenderWeaponUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Weapons")) {
			if (upgradeIndices_.machineGun) ImGui::BeginDisabled();
			if (ImGui::Button("Machine Gun", buttonSize)) {
				upgradeIndices_.machineGun = true;
				ImGui::BeginDisabled();
			}
			if (upgradeIndices_.machineGun) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.energyCannon) ImGui::BeginDisabled();
			if (ImGui::Button("Energy Cannon", buttonSize)) {
				upgradeIndices_.energyCannon = true;
				ImGui::BeginDisabled();
			}
			if (upgradeIndices_.energyCannon) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
	
	void Upgrades::RenderSpeedUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Speed")) {
			if(upgradeIndices_.speed != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Speed I", buttonSize)) {
				++upgradeIndices_.speed;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.speed != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.speed != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Speed II", buttonSize)) {
				++upgradeIndices_.speed;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.speed != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.speed != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Mud Pool\nEffectiveness", buttonSize)) {
				++upgradeIndices_.speed;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.speed != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
	
	void Upgrades::RenderHealthUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Health")) {
			if (upgradeIndices_.health != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Health I", buttonSize)) {
				++upgradeIndices_.health;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.health != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.health != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Health II", buttonSize)) {
				++upgradeIndices_.health;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.health != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.health != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Acid Pool\nEffectiveness", buttonSize)) {
				++upgradeIndices_.health;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.health != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}

	void Upgrades::RenderEnergyUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Energy")) {
			if (upgradeIndices_.energy != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Energy I", buttonSize)) {
				++upgradeIndices_.energy;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.energy != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.energy != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Energy II", buttonSize)) {
				++upgradeIndices_.energy;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.energy != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (upgradeIndices_.energy != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Geyser\nEffectiveness", buttonSize)) {
				++upgradeIndices_.energy;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (upgradeIndices_.energy != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
}
