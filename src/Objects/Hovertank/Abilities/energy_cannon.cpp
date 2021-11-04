#include "Objects/Hovertank/Abilities/energy_cannon.h"

namespace game {
	EnergyCannon::EnergyCannon(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) 
		: Ability(5.0f), SceneNode(name, geometry, material, texture) {

	}

	EnergyCannon::~EnergyCannon() {

	}

	// Update geometry configuration
	void EnergyCannon::Update(void) {
		UpdateCooldown();
	}

	void EnergyCannon::UseAbility(Projectile** outProj, glm::vec3 forward, Resource* geometry, Resource* material, Resource* texture) {
		if (cooldown_ > 0) return; // need to wait

		static int num = 0; // used to give unique names to each projectile
		*outProj = new ParabolicProjectile("EnergyCannonProjectile" + std::to_string(num++), geometry, material, texture);
		(*outProj)->SetVelocity((forward + glm::vec3(0.0f, 1.0f, 0.0f)) * 10.0f); // make it slightly angled
		(*outProj)->SetLifespan(5.0f);
		projectiles_.push_back(*outProj);

		StartCooldown();
	}
} // namespace game