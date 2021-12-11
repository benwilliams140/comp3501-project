#include "Objects/Hovertank/Abilities/energy_cannon.h"
#include "Control/game.h"
#include "Control/GUI/menu.h"

namespace game {
	EnergyCannon::EnergyCannon(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) 
		: Ability(name, geometry, material, texture) {
		SetMaxCooldown(2.5f);
		SetHUDTexture(Menu::LoadImage("parabolic.png"));
	}

	EnergyCannon::~EnergyCannon() {

	}

	// Update geometry configuration
	void EnergyCannon::Update(void) {
		UpdateCooldown();
	}

	Projectile* EnergyCannon::UseAbility(glm::vec3 position, glm::vec3 forward)
	{
		if (cooldown_ > 0) return nullptr; // need to wait

		static int num = 0; // used to give unique names to each projectile
		ParabolicProjectile* proj = Game::GetInstance().CreateInstance<ParabolicProjectile>("EnergyCannonProjectile" + std::to_string(num++), "RubberBullet", "Simple", "RubberTexture");
		// set properties for this new projectile
		proj->SetPosition(position);
		proj->SetScale(glm::vec3(1.25f));
		proj->SetVelocity(forward * 25.0f + glm::vec3(0.0f, 1.5f, 0.0f) * 10.0f); // make it slightly angled
		proj->SetLifespan(5.0f);
		projectiles_.push_back(proj);

		StartCooldown();

		return proj;
	}
} // namespace game