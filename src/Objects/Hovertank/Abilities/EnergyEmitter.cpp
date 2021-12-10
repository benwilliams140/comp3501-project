#include "Objects/Hovertank/Abilities/EnergyEmitter.h"
#include "Control/game.h"
#include "Control/GUI/menu.h"

namespace game {

	EnergyEmitter::EnergyEmitter(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture)
		: Ability(name, geometry, material, texture) {
		SetMaxCooldown(45.5f);
		SetHUDTexture(Menu::LoadImage("energy_blast.png"));//have to change this later
	}


	EnergyEmitter::~EnergyEmitter() {

	}


	void EnergyEmitter::Update(void) {
		UpdateCooldown();
	}

	Projectile* EnergyEmitter::UseAbility(glm::vec3 position, glm::vec3 forward)
	{
		if (cooldown_ > 0) return nullptr; // need to wait

		static int num = 0; // used to give unique names to each projectile
		EnergyBlast* eb = Game::GetInstance().CreateInstance<EnergyBlast>("EnergyBlast" + std::to_string(num++), "Sphere", "eb_shader", "EnergyBlastTexture");
		eb->SetPosition(position);//position should be tanks position
		eb->SetScale(glm::vec3(5.0f));
		eb->SetLifespan(5.5f);
		projectiles_.push_back(eb);

		StartCooldown();

		return eb;
	}

} // namespace game 