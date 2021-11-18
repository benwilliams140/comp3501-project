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
		ImVec2 windowSize = ImVec2(windowWidth, windowHeight);

		RenderPoints(points, windowSize);
		RenderWeaponUpgrades(points, buttonSize);
		RenderSpeedUpgrades(points, buttonSize);
		RenderHealthUpgrades(points, buttonSize);
		RenderEnergyUpgrades(points, buttonSize);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Upgrades::RenderPoints(int points, ImVec2 windowSize) {
		float pointsWidth = windowSize.x * pointsLabel_.widthRatio;
		float pointsHeight = windowSize.y * pointsLabel_.heightRatio;
		float pointsX = windowSize.x - pointsWidth - 5.0f;
		float pointsY = 5.0f;

		ImGui::SetCursorPos(ImVec2(pointsX, pointsY));
		ImGui::Text(std::to_string(points).c_str());
	}

	void Upgrades::RenderWeaponUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Weapons")) {
			if (weaponUpgrade_.machineGun) ImGui::BeginDisabled();
			if (ImGui::Button("Machine Gun", buttonSize) && points >= weaponUpgrade_.machineGunCost) {
				weaponUpgrade_.machineGun = true;
				Game::GetInstance().GetPlayer()->AddMoney(-weaponUpgrade_.machineGunCost);
				ImGui::BeginDisabled();
			}
			if (weaponUpgrade_.machineGun) ImGui::EndDisabled();
			ImGui::SameLine();
			if (weaponUpgrade_.energyCannon) ImGui::BeginDisabled();
			if (ImGui::Button("Energy Cannon", buttonSize) && points >= weaponUpgrade_.energyCannonCost) {
				weaponUpgrade_.energyCannon = true;
				Game::GetInstance().GetPlayer()->AddMoney(-weaponUpgrade_.energyCannonCost);
				ImGui::BeginDisabled();
			}
			if (weaponUpgrade_.energyCannon) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
	
	void Upgrades::RenderSpeedUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Speed")) {
			if(speedUpgrade_.index != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Speed I", buttonSize) && points >= speedUpgrade_.cost) {
				++speedUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-speedUpgrade_.cost);
				speedUpgrade_.cost *= speedUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (speedUpgrade_.index  != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (speedUpgrade_.index  != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Speed II", buttonSize) && points >= speedUpgrade_.cost) {
				++speedUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-speedUpgrade_.cost);
				speedUpgrade_.cost *= speedUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (speedUpgrade_.index  != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (speedUpgrade_.index  != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Mud Pool\nEffectiveness", buttonSize) && points >= speedUpgrade_.cost) {
				++speedUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-speedUpgrade_.cost);
				speedUpgrade_.cost *= speedUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (speedUpgrade_.index  != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
	
	void Upgrades::RenderHealthUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Health")) {
			if (healthUpgrade_.index  != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Health I", buttonSize) && points >= healthUpgrade_.cost) {
				++healthUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-healthUpgrade_.cost);
				healthUpgrade_.cost *= healthUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (healthUpgrade_.index  != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (healthUpgrade_.index  != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Health II", buttonSize) && points >= healthUpgrade_.cost) {
				++healthUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-healthUpgrade_.cost);
				healthUpgrade_.cost *= healthUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (healthUpgrade_.index  != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (healthUpgrade_.index  != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Acid Pool\nEffectiveness", buttonSize) && points >= healthUpgrade_.cost) {
				++healthUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-healthUpgrade_.cost);
				healthUpgrade_.cost *= healthUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (healthUpgrade_.index  != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}

	void Upgrades::RenderEnergyUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Energy")) {
			if (energyUpgrade_.index  != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Energy I", buttonSize) && points >= energyUpgrade_.cost) {
				++energyUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-energyUpgrade_.cost);
				energyUpgrade_.cost *= energyUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (energyUpgrade_.index  != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (energyUpgrade_.index  != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Energy II", buttonSize) && points >= energyUpgrade_.cost) {
				++energyUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-energyUpgrade_.cost);
				energyUpgrade_.cost *= energyUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (energyUpgrade_.index  != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (energyUpgrade_.index  != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Geyser\nEffectiveness", buttonSize) && points >= energyUpgrade_.cost) {
				++energyUpgrade_.index;
				Game::GetInstance().GetPlayer()->AddMoney(-energyUpgrade_.cost);
				energyUpgrade_.cost *= energyUpgrade_.multiplier;
				ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
			}
			if (energyUpgrade_.index  != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
}
