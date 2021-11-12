#include "Objects/Hovertank/Abilities/machine_gun.h"
#include "Control/game.h"
#include "Control/GUI/menu.h"

namespace game {

	MachineGun::MachineGun(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) 
		: Ability(0.25f, Menu::LoadImage("linear.png")), SceneNode(name, geometry, material, texture) {
	}


	MachineGun::~MachineGun() {

	}


	void MachineGun::Update(void) {
		UpdateCooldown();
	}

	Projectile* MachineGun::UseAbility(glm::vec3 position, glm::vec3 forward)
	{
		if (cooldown_ > 0) return nullptr; // need to wait

		static int num = 0; // used to give unique names to each projectile
		LinearProjectile* proj = Game::GetInstance().CreateInstance<LinearProjectile>("MachineGunProjectile" + std::to_string(num++), "Cube", "Simple", "RockyTexture");
		proj->SetPosition(position);
		proj->SetScale(glm::vec3(0.5));
		proj->SetVelocity(forward * 50.0f);
		proj->SetLifespan(3.0f);
		projectiles_.push_back(proj);

		StartCooldown();

		return proj;
	}

} // namespace game 