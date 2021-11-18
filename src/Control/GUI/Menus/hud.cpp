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

		ImVec2 windowSize = ImVec2(windowWidth, windowHeight);
		ImVec2 windowRatio = ImVec2((float) windowWidth / initialWindowWidth, (float) windowHeight / initialWindowHeight);
		RenderHealthBar(windowSize, windowRatio);
		RenderEnergyBar(windowSize, windowRatio);
		RenderProjectileSelection(windowSize, windowRatio);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void HUD::RenderHealthBar(ImVec2 windowSize, ImVec2 windowRatio) {
		// calculate health bar position and size
		float health = Game::GetInstance().GetPlayer()->GetHealth();
		// outer rectangle
		float healthBarBaseWidth = windowSize.x * healthBar_.widthRatio;
		float healthBarBaseHeight = windowSize.y * healthBar_.heightRatio;
		float healthBarBaseX = windowSize.x / 2 - healthBarBaseWidth / 2;
		float healthBarBaseY = 5 * windowRatio.y;
		// inner rectangle
		float healthBarWidth = (healthBarBaseWidth - 20.0f * windowRatio.x) * health / Game::GetInstance().GetPlayer()->GetMaxHealth();
		float healthBarHeight = healthBarBaseHeight - 20.0f * windowRatio.y;
		float healthBarX = healthBarBaseX + 10.0f * windowRatio.x;
		float healthBarY = healthBarBaseY + 11.0f * windowRatio.y;

		// render the health bar
		ImGui::GetWindowDrawList()->AddImage(healthBar_.backgroundImage, ImVec2(healthBarBaseX, healthBarBaseY), ImVec2(healthBarBaseX + healthBarBaseWidth, healthBarBaseY + healthBarBaseHeight));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(healthBarX, healthBarY), ImVec2(healthBarX + healthBarWidth, healthBarY + healthBarHeight), healthBar_.foregroundColor, 0.0f, 0);
	}

	void HUD::RenderEnergyBar(ImVec2 windowSize, ImVec2 windowRatio) {
		// calculate energy bar positions and sizes
		float energy = Game::GetInstance().GetPlayer()->GetEnergy();
		// outer rectangle
		float energyBarBaseWidth = windowSize.x * energyBar_.widthRatio;
		float energyBarBaseHeight = windowSize.y * energyBar_.heightRatio;
		float energyBarBaseX = windowSize.x - energyBarBaseWidth - 2.0f * windowRatio.x;
		float energyBarBaseY = windowSize.y - energyBarBaseHeight - 2.0f * windowRatio.y;
		// inner rectangle
		float energyBarWidth = energyBarBaseWidth - 38.0f * windowRatio.x;
		float energyBarHeight = (energyBarBaseHeight - 10.0f * windowRatio.y) * energy / Game::GetInstance().GetPlayer()->GetMaxEnergy();
		float energyBarX = energyBarBaseX + 20.5f * windowRatio.x;
		float energyBarY = energyBarBaseY + energyBarBaseHeight - 5.0f * windowRatio.y - energyBarHeight;

		// render the energy bar (can replace the base colour with an image)
		ImGui::GetWindowDrawList()->AddImage(energyBar_.backgroundImage, ImVec2(energyBarBaseX, energyBarBaseY), ImVec2(energyBarBaseX + energyBarBaseWidth, energyBarBaseY + energyBarBaseHeight));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(energyBarX, energyBarY), ImVec2(energyBarX + energyBarWidth, energyBarY + energyBarHeight), energyBar_.foregroundColor, 0.0f, 0);
	}

	void HUD::RenderProjectileSelection(ImVec2 windowSize, ImVec2 windowRatio) {
		HoverTankTurret* turret = Game::GetInstance().GetPlayer()->GetTank()->GetTurret();
		float projSelectionWidth = windowSize.x * projSelection_.widthRatio;
		float projSelectionHeight = windowSize.y * projSelection_.heightRatio;
		float projSelectionX = windowSize.x / 2 - projSelectionWidth / 2;
		float projSelectionY = windowSize.y - projSelectionHeight - 5;

		// can add a background image instead
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(projSelectionX, projSelectionY), ImVec2(projSelectionX + projSelectionWidth, projSelectionY + projSelectionHeight), projSelection_.backgroundColor, 0.0f, 0);
		
		// render square for the abilities
		std::vector<Ability*> abilities = turret->GetAbilities();

		const float abilityGapX = 2.5f * windowRatio.x;
		const float abilityGapY = 2.5f * windowRatio.y;
		const float totalAbilityGapX = abilityGapX * (turret->GetMaxAbilities() + 1);
		const float abilityWidth = (projSelectionWidth - totalAbilityGapX) / turret->GetMaxAbilities();
		const float abilityHeight = projSelectionHeight - abilityGapY * 2;
		for (int i = 0; i < turret->GetMaxAbilities(); ++i) {
			float abilityX = projSelectionX + abilityGapX + (abilityWidth + abilityGapX) * i;
			float abilityY = projSelectionY + abilityGapY;
			
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