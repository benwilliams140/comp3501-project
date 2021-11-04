#include "Objects/Hovertank/Abilities/machine_gun.h"

namespace game {

	MachineGun::MachineGun(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) 
		: Ability(0.25f), SceneNode(name, geometry, material, texture) {
	}


	MachineGun::~MachineGun() {

	}


	void MachineGun::Update(void) {
		UpdateCooldown();
	}

	void MachineGun::UseAbility(Projectile** outProj, glm::vec3 forward, Resource* geometry, Resource* material, Resource* texture) {
		if (cooldown_ > 0) return; // need to wait

		static int num = 0; // used to give unique names to each projectile
		*outProj = new LinearProjectile("MachineGunProjectile" + std::to_string(num++), geometry, material, texture);
		(*outProj)->SetVelocity(forward * 50.f);
		(*outProj)->SetLifespan(3.0f);
		projectiles_.push_back(*outProj);

		StartCooldown();
	}

} // namespace game 