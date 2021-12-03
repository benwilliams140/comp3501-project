#include "Objects/Hovertank/Abilities/ability.h"

namespace game {
	Ability::Ability(std::string name, const Resource* geom, const Resource* mat, const Resource* tex) : SceneNode(name, geom, mat, tex)
	{
		maxCooldown_ = cooldown_ = 0.0f;
		hudTexture_ = NULL;
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

	void Ability::SetMaxCooldown(float maxCooldown)
	{
		maxCooldown_ = maxCooldown;
	}

	void Ability::SetHUDTexture(ImTextureID hudTexture)
	{
		hudTexture_ = hudTexture;
	}
}; // namespace game