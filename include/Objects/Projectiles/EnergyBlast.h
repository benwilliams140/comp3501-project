#ifndef ENERGYBLAST_H_
#define ENERGYBLAST_H_

#include "Objects/Projectiles/projectile.h"

namespace game {

	// Abstraction of an Projectile
	class EnergyBlast : public Projectile{

	public:
		// Create Projectile from given resources
		EnergyBlast(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);
		
		// Destructor
		~EnergyBlast();

		virtual Math::SphereCollider GetCollider(void) const override;
		virtual void EnemyCollision() override;
		// Update geometry configuration
		virtual void Update() override;
	}; // class Projectile

} // namespace game

#endif // ENERGYBLAST_H_