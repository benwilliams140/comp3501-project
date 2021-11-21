#include "Objects/Projectiles/Enemy_linear_projectile.h"

namespace game {

	EnemyLinearProjectile::EnemyLinearProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Projectile(name, geometry, material, texture) {
		attack_pow = 10.0f;
	}


	EnemyLinearProjectile::~EnemyLinearProjectile() {
	}

	void EnemyLinearProjectile::Update() {
		//update postion
		Translate(velocity_ * Time::GetDeltaTime());
		lifespan_ -= Time::GetDeltaTime();
	}

} // namespace game 