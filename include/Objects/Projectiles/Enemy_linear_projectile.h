#ifndef ENEMY_LINEAR_PROJECTILE_H_
#define ENEMY_LINEAR_PROJECTILE_H_

#include "Objects/Projectiles/projectile.h"

namespace game {

	// Abstraction of an Projectile
	class EnemyLinearProjectile : public Projectile {

	public:
		// Create EnemyLinearProjectile from given resources
		EnemyLinearProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~EnemyLinearProjectile();

		// Update geometry configuration
		virtual void Update() override;
		void TankCollision();
	private:
		float attack_pow;
	}; // class EnemyLinearProjectile

} // namespace game

#endif // EnemyLinearProjectile_H_
