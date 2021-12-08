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

		ImGui::PushStyleColor(ImGuiCol_Text, pointsLabel_.textColor);
		RenderPoints(points, windowSize);
		ImGui::PopStyleColor(1);

		ImGui::PushStyleColor(ImGuiCol_Text, button_.textColor);
		ImGui::PushFont(button_.font);
		RenderWeaponUpgrades(points, buttonSize);
		RenderSpeedUpgrades(points, buttonSize);
		RenderHealthUpgrades(points, buttonSize);
		RenderEnergyUpgrades(points, buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(1);

		ImGui::End();

		// render the TextWindow on top of everything
		Game::GetInstance().GetMenu(MenuType::TEXT_WINDOW)->Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Upgrades::RenderPoints(int points, ImVec2 windowSize) {
		float pointsWidth = windowSize.x * pointsLabel_.widthRatio;
		float pointsHeight = windowSize.y * pointsLabel_.heightRatio;
		float pointsX = windowSize.x - pointsWidth - 5.0f;
		float pointsY = 5.0f;

		ImGui::SetCursorPos(ImVec2(pointsX, pointsY));
		ImGui::PushFont(pointsLabel_.font);
		ImGui::Text(std::to_string(points).c_str());
		ImGui::PopFont();
	}

	void Upgrades::RenderWeaponUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Weapons")) {
			std::string hovertankMaterial = "Simple";
			HoverTank* tank = Game::GetInstance().GetPlayer()->GetTank();
			if (weaponUpgrade_.machineGun) ImGui::BeginDisabled();
			if (ImGui::Button("Machine Gun", buttonSize) && points >= weaponUpgrade_.machineGunCost) {
				weaponUpgrade_.machineGun = true;
				Game::GetInstance().GetPlayer()->AddMoney(-weaponUpgrade_.machineGunCost);
				
				MachineGun* machine_gun = Game::GetInstance().CreateInstance<MachineGun>("MachineGun", HOVERTANK_MACHINE_GUN, hovertankMaterial, "uv6");
				machine_gun->Rotate(glm::angleAxis(glm::radians(180.0f), tank->GetForward()));
				machine_gun->Translate(glm::vec3(0.0f, 0.2555f, 0.0f));
				machine_gun->Scale(glm::vec3(0.75));
				machine_gun->SetParent(tank->GetTurret());
				machine_gun->SetActive(false);

				// Create Care Package
				CarePackage* package = Game::GetInstance().CreateInstance<CarePackage>("Package", "Cube", "Simple", "Crate");
				package->SetPosition(glm::vec3(-30.0f, 35.0f, 75.0f));
				package->SetStoredAbility(machine_gun);
				
				ImGui::BeginDisabled();
			}
			if (weaponUpgrade_.machineGun) ImGui::EndDisabled();
			ImGui::SameLine();
			if (weaponUpgrade_.energyCannon) ImGui::BeginDisabled();
			if (ImGui::Button("Energy Cannon", buttonSize) && points >= weaponUpgrade_.energyCannonCost) {
				weaponUpgrade_.energyCannon = true;
				Game::GetInstance().GetPlayer()->AddMoney(-weaponUpgrade_.energyCannonCost);
				
				EnergyCannon* energy_cannon = Game::GetInstance().CreateInstance<EnergyCannon>("MachineGun", HOVERTANK_MACHINE_GUN, hovertankMaterial, "uv6");
				energy_cannon->Rotate(glm::angleAxis(glm::radians(180.0f), tank->GetForward()));
				energy_cannon->Translate(glm::vec3(0.0f, 0.2555f, 0.0f));
				energy_cannon->Scale(glm::vec3(0.75));
				energy_cannon->SetParent(tank->GetTurret());
				energy_cannon->SetActive(false);

				// Create Care Package
				CarePackage* package = Game::GetInstance().CreateInstance<CarePackage>("Package", "Cube", "Simple", "Crate");
				package->SetPosition(glm::vec3(-30.0f, 35.0f, 75.0f));
				package->SetStoredAbility(energy_cannon);
				
				ImGui::BeginDisabled();
			}
			if (weaponUpgrade_.energyCannon) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}

	void Upgrades::HandleSpeedUpgradeButtonClick() {
		++speedUpgrade_.index;
		Game::GetInstance().GetPlayer()->AddMoney(-speedUpgrade_.cost);
		speedUpgrade_.cost *= speedUpgrade_.multiplier;
		ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
	}

	void Upgrades::HandleHealthUpgradeButtonClick()
	{
		++healthUpgrade_.index;
		Game::GetInstance().GetPlayer()->AddMoney(-healthUpgrade_.cost);
		healthUpgrade_.cost *= healthUpgrade_.multiplier;
		ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
	}

	void Upgrades::HandleEnergyUpgradeButtonClick()
	{
		++energyUpgrade_.index;
		Game::GetInstance().GetPlayer()->AddMoney(-energyUpgrade_.cost);
		energyUpgrade_.cost *= energyUpgrade_.multiplier;
		ImGui::BeginDisabled(); // must call this before calling the next EndDisabled
	}
	
	void Upgrades::RenderSpeedUpgrades(int points, ImVec2 buttonSize)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		if (ImGui::TreeNode("Speed")) {
			if(speedUpgrade_.index != 0) ImGui::BeginDisabled();
			if (ImGui::Button("+ Speed I", buttonSize) && points >= speedUpgrade_.cost) {
				Game::GetInstance().GetPlayer()->GetTank()->IncreaseSpeedMultiple(speedUpgrade_.increase);
				HandleSpeedUpgradeButtonClick();
			}
			if (speedUpgrade_.index  != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (speedUpgrade_.index  != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Speed II", buttonSize) && points >= speedUpgrade_.cost) {
				Game::GetInstance().GetPlayer()->GetTank()->IncreaseSpeedMultiple(speedUpgrade_.increase);
				HandleSpeedUpgradeButtonClick();
			}
			if (speedUpgrade_.index  != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (speedUpgrade_.index  != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Mud Pool\nEffectiveness", buttonSize) && points >= speedUpgrade_.cost) {
				Game::GetInstance().SetHazardEffectiveness<MudPool>(0.7f); // treated as an inverse (eg. 0.5f will allow faster movement than 0.25f)
				HandleSpeedUpgradeButtonClick();
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
				Game::GetInstance().GetPlayer()->SetMaxHealth(Game::GetInstance().GetPlayer()->GetMaxHealth() + healthUpgrade_.increase);
				HandleHealthUpgradeButtonClick();
			}
			if (healthUpgrade_.index  != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (healthUpgrade_.index  != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Health II", buttonSize) && points >= healthUpgrade_.cost) {
				Game::GetInstance().GetPlayer()->SetMaxHealth(Game::GetInstance().GetPlayer()->GetMaxHealth() + healthUpgrade_.increase);
				HandleHealthUpgradeButtonClick();
			}
			if (healthUpgrade_.index  != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (healthUpgrade_.index  != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Acid Pool\nEffectiveness", buttonSize) && points >= healthUpgrade_.cost) {
				Game::GetInstance().SetHazardEffectiveness<AcidPool>(0.5f);
				HandleHealthUpgradeButtonClick();
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
				Game::GetInstance().GetPlayer()->SetMaxEnergy(Game::GetInstance().GetPlayer()->GetMaxEnergy() + energyUpgrade_.increase);
				HandleEnergyUpgradeButtonClick();
			}
			if (energyUpgrade_.index  != 0) ImGui::EndDisabled();
			ImGui::SameLine();
			if (energyUpgrade_.index  != 1) ImGui::BeginDisabled();
			if (ImGui::Button("+ Energy II", buttonSize) && points >= energyUpgrade_.cost) {
				Game::GetInstance().GetPlayer()->SetMaxEnergy(Game::GetInstance().GetPlayer()->GetMaxEnergy() + energyUpgrade_.increase);
				HandleEnergyUpgradeButtonClick();
			}
			if (energyUpgrade_.index  != 1) ImGui::EndDisabled();
			ImGui::SameLine();
			if (energyUpgrade_.index  != 2) ImGui::BeginDisabled();
			if (ImGui::Button("- Geyser\nEffectiveness", buttonSize) && points >= energyUpgrade_.cost) {
				Game::GetInstance().SetHazardEffectiveness<Geyser>(0.1f); // value in [0,1]
				HandleEnergyUpgradeButtonClick();
			}
			if (energyUpgrade_.index  != 2) ImGui::EndDisabled();
			ImGui::TreePop();
		}
	}
}
