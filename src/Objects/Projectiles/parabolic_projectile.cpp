#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

#include "Objects/Projectiles/parabolic_projectile.h"

namespace game {

	ParabolicProjectile::ParabolicProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Projectile(name, geometry, material, texture) {
		breakable_ = true;
	}


	ParabolicProjectile::~ParabolicProjectile() {
	}

	void ParabolicProjectile::Update() {
		//update position
		Translate(velocity_ * Time::GetDeltaTime());
		lifespan_ -= Time::GetDeltaTime();

		//update velocity so it will have a parabolic trajectory
		velocity_ -= glm::vec3(0, gravity_, 0) * Time::GetDeltaTime();
		EnemyCollision();
		ArtifactCollision();
	}

} // namespace game 