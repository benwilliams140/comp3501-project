#include "Objects/Hovertank/Abilities/ability.h"

namespace game {
	Ability::Ability(float maxCooldown, ImTextureID hudTexture) {
		cooldown_ = 0.0f;
		maxCooldown_ = maxCooldown;
		hudTexture_ = hudTexture;
	}

	Ability::~Ability() {

	}

	void Ability::UpdateCooldown() {
		cooldown_ = std::max(cooldown_ - Time::GetDeltaTime(), 0.0f);
	}

	void Ability::StartCooldown() {
		cooldown_ = maxCooldown_;
	}

	std::vector<Projectile*> Ability::RemoveDeadProjectiles() {
		std::vector<Projectile*> projectilesToRemove;
		
		//goes through entire list of projectiles, if it's dead get rid of it
		for (int i = projectiles_.size() - 1; i >= 0; i--) {
			if (!projectiles_[i]->IsAlive()) {
				projectilesToRemove.push_back(projectiles_[i]);
				projectiles_.erase(projectiles_.begin() + i);
			}
		}

		return projectilesToRemove;
	}

	std::vector<Projectile*> Ability::GetProjectiles() {
		return projectiles_;
	}

	float Ability::GetCooldown() {
		return cooldown_;
	}

	float Ability::GetMaxCooldown() {
		return maxCooldown_;
	}
	ImTextureID Ability::GetHUDTexture()
	{
		return hudTexture_;
	}
}; // namespace game