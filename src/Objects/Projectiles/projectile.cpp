#include "Objects/Projectiles/projectile.h"

namespace game {
	Projectile::Projectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		// lifespan must be set using SetLifespan
	}

	Projectile::~Projectile() {

	}

	void Projectile::SetVelocity(glm::vec3 vel) {
		velocity_ = vel;
	}

	void Projectile::SetLifespan(float lifespan) {
		lifespan_ = lifespan; // in seconds
	}

	bool Projectile::IsAlive() {
		return lifespan_ > 0;
	}
}; // namespace game