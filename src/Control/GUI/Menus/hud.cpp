#include "Control/GUI/Menus/hud.h"
#include "Control/game.h"
#include "Control/input.h"

namespace game {
	HUD::HUD() : Menu() {

	}

	HUD::~HUD() {

	}

	void HUD::HandleInput() {
		HoverTankTurret* turret = Game::GetInstance().GetPlayer()->GetTank()->GetTurret();

		glm::vec2 scroll = Input::getMouseScroll();
		if (scroll.y < 0) { // select next ability when the mouse is scrolled down
			turret->SelectNextAbility();
		}
		else if (scroll.y > 0) { // select previous ability when the mouse is scrolled up
			turret->SelectPreviousAbility();
		}

		// might be a better way of doing this with a new function in the input class
		int index = -1;
		if (Input::getKey(INPUT_KEY_1)) {
			index = 0;
		}
		else if (Input::getKey(INPUT_KEY_2)) {
			index = 1;
		}
		else if (Input::getKey(INPUT_KEY_3)) {
			index = 2;
		}
		else if (Input::getKey(INPUT_KEY_4)) {
			index = 3;
		}

		// index is valid
		if (turret->GetAbilities().size() > index && index != -1) {
			while (turret->GetSelectedIndex() != index) {
				if (index < turret->GetSelectedIndex()) turret->SelectPreviousAbility();
				else turret->SelectNextAbility();
			}
		}
	}
	
	void HUD::Render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int windowWidth, windowHeight;
		glfwGetWindowSize(Game::GetInstance().GetWindow(), &windowWidth, &windowHeight);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize | 
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin("HUD", (bool*)true, flags);

		RenderHealthBar(windowWidth, windowHeight);
		RenderEnergyBar(windowWidth, windowHeight);
		RenderProjectileSelection(windowWidth, windowHeight);

		// render the energy bar (can replace the base colour with an image)

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void HUD::RenderHealthBar(int windowWidth, int windowHeight) {
		// calculate health bar position and size
		float health = Game::GetInstance().GetPlayer()->GetHealth();
		// outer rectangle
		float healthBarBaseWidth = windowWidth * healthBar_.widthRatio;
		float healthBarBaseHeight = windowHeight * healthBar_.heightRatio;
		float healthBarBaseX = windowWidth / 2 - healthBarBaseWidth / 2;
		float healthBarBaseY = 5;
		// inner rectangle
		float healthBarWidth = (healthBarBaseWidth - 20.0f) * health / Game::GetInstance().GetPlayer()->GetMaxHealth();
		float healthBarHeight = healthBarBaseHeight - 20.0f;
		float healthBarX = healthBarBaseX + 10.0f;
		float healthBarY = healthBarBaseY + 11.0f;

		// render the health bar
		ImGui::GetWindowDrawList()->AddImage(healthBar_.backgroundImage, ImVec2(healthBarBaseX, healthBarBaseY), ImVec2(healthBarBaseX + healthBarBaseWidth, healthBarBaseY + healthBarBaseHeight));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(healthBarX, healthBarY), ImVec2(healthBarX + healthBarWidth, healthBarY + healthBarHeight), healthBar_.foregroundColor, 0.0f, 0);
	}

	void HUD::RenderEnergyBar(int windowWidth, int windowHeight) {
		// calculate energy bar positions and sizes
		float energy = Game::GetInstance().GetPlayer()->GetEnergy();
		// outer rectangle
		float energyBarBaseWidth = windowWidth * energyBar_.widthRatio;
		float energyBarBaseHeight = windowHeight * energyBar_.heightRatio;
		float energyBarBaseX = windowWidth - energyBarBaseWidth - 2.0f;
		float energyBarBaseY = windowHeight - energyBarBaseHeight - 2.0f;
		// inner rectangle
		float energyBarWidth = energyBarBaseWidth - 38.0f;
		float energyBarHeight = (energyBarBaseHeight - 10.0f) * energy / Game::GetInstance().GetPlayer()->GetMaxEnergy();
		float energyBarX = energyBarBaseX + 20.5f;
		float energyBarY = energyBarBaseY + energyBarBaseHeight - 5.0f - energyBarHeight;

		// render the energy bar (can replace the base colour with an image)
		ImGui::GetWindowDrawList()->AddImage(energyBar_.backgroundImage, ImVec2(energyBarBaseX, energyBarBaseY), ImVec2(energyBarBaseX + energyBarBaseWidth, energyBarBaseY + energyBarBaseHeight));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(energyBarX, energyBarY), ImVec2(energyBarX + energyBarWidth, energyBarY + energyBarHeight), energyBar_.foregroundColor, 0.0f, 0);
	}

	void HUD::RenderProjectileSelection(int windowWidth, int windowHeight) {
		HoverTankTurret* turret = Game::GetInstance().GetPlayer()->GetTank()->GetTurret();
		float projSelectionWidth = windowWidth * projSelection_.widthRatio;
		float projSelectionHeight = windowHeight * projSelection_.heightRatio;
		float projSelectionX = windowWidth / 2 - projSelectionWidth / 2;
		float projSelectionY = windowHeight - projSelectionHeight - 5;

		// can add a background image instead
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(projSelectionX, projSelectionY), ImVec2(projSelectionX + projSelectionWidth, projSelectionY + projSelectionHeight), projSelection_.backgroundColor, 0.0f, 0);
		
		// render square for the abilities
		std::vector<Ability*> abilities = turret->GetAbilities();

		const float abilityGap = 2.5f;
		const float totalAbilityGap = abilityGap * (turret->GetMaxAbilities() + 1);
		const float abilityWidth = (projSelectionWidth - totalAbilityGap) / turret->GetMaxAbilities();
		const float abilityHeight = projSelectionHeight - abilityGap * 2;
		for (int i = 0; i < turret->GetMaxAbilities(); ++i) {
			float abilityX = projSelectionX + abilityGap + (abilityWidth + abilityGap) * i;
			float abilityY = projSelectionY + abilityGap;
			
			// renders the image for each available ability
			// renders the rectangle showing the cooldown on each ability
			// note that not all abilities in the inventory are necessarily filled
			if (i < abilities.size()) {
				ImGui::GetWindowDrawList()->AddImage(abilities.at(i)->GetHUDTexture(), ImVec2(abilityX, abilityY), ImVec2(abilityX + abilityWidth, abilityY + abilityHeight));

				float cooldownHeight = abilityHeight * abilities.at(i)->GetCooldown() / abilities.at(i)->GetMaxCooldown();
				float cooldownY = abilityY + abilityHeight - cooldownHeight;
				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(abilityX, cooldownY), ImVec2(abilityX + abilityWidth, cooldownY + cooldownHeight), projSelection_.cooldownColor, 0.0f, 0);
			}
			// render a blank rectangle where abilities aren't filled
			else {
				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(abilityX, abilityY), ImVec2(abilityX + abilityWidth, abilityY + abilityHeight), projSelection_.abilityColor, 0.0f, 0);
			}

			// renders the rectangle showing which ability is selected
			if (i == turret->GetSelectedIndex()) {
				ImGui::GetWindowDrawList()->AddRect(ImVec2(abilityX, abilityY), ImVec2(abilityX + abilityWidth, abilityY + abilityHeight), projSelection_.selectedColor, 0.0f, 0);
			}
		}
	}
} // namespace game