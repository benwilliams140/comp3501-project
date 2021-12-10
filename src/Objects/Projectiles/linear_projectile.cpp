#include "Objects/Projectiles/linear_projectile.h"

namespace game {

	LinearProjectile::LinearProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Projectile(name, geometry, material, texture) {
		breakable_ = true;
	}


	LinearProjectile::~LinearProjectile() {
	}

	void LinearProjectile::Update() {
		//update postion
		Translate(velocity_ * Time::GetDeltaTime());
		lifespan_ -= Time::GetDeltaTime();
		EnemyCollision();
		ArtifactCollision();
	}

} // namespace game 