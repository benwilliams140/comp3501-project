#include "Objects/Hovertank/Abilities/energy_cannon.h"
#include "Control/game.h"
#include "Control/GUI/menu.h"

namespace game {
	EnergyCannon::EnergyCannon(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) 
		: Ability(5.0f, Menu::LoadImage("parabolic.png")), SceneNode(name, geometry, material, texture) {

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
		// creates a new parabolic projectile and stores it in the outProj pointer
		*outProj = new ParabolicProjectile("EnergyCannonProjectile" + std::to_string(num++), geometry, material, texture);
		// set properties for this new projectile
		(*outProj)->SetVelocity((forward + glm::vec3(0.0f, 1.0f, 0.0f)) * 10.0f); // make it slightly angled
		(*outProj)->SetLifespan(5.0f);
		
		projectiles_.push_back(*outProj);

		StartCooldown();
	}
	Projectile* EnergyCannon::UseAbility(glm::vec3 position, glm::vec3 forward)
	{
		if (cooldown_ > 0) return nullptr; // need to wait

		static int num = 0; // used to give unique names to each projectile
		ParabolicProjectile* proj = Game::GetInstance().CreateInstance<ParabolicProjectile>("EnergyCannonProjectile" + std::to_string(num++), "Cube", "Simple", "RockyTexture");
		// set properties for this new projectile
		proj->SetPosition(position);
		proj->SetScale(glm::vec3(0.5));
		proj->SetVelocity((forward + glm::vec3(0.0f, 1.0f, 0.0f)) * 10.0f); // make it slightly angled
		proj->SetLifespan(5.0f);
		projectiles_.push_back(proj);

		StartCooldown();

		return proj;
	}
} // namespace game