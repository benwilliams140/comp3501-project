#include "Objects/Projectile.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	Projectile::Projectile(const std::string name, const Resource* geometry, const Resource* material, glm::vec3 vel) : SceneNode(name, geometry, material) {
		velocity = vel;
		alive = true;
		lifeSpan = 500;
		colliderBox_x = 10;
		colliderBox_y = 10;
		colliderBox_z = 10;
	}


	Projectile::~Projectile() {
	}


	glm::quat Projectile::GetAngM(void) const {

		return angm_;
	}


	void Projectile::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void Projectile::Update(void) {
		//update postion
		SetPosition(GetPosition() + velocity);

		//lower lifespan
		if (lifeSpan > 0) {
			lifeSpan--;
		}
		else {
			alive = false;
		}
	}

	bool Projectile::isAlive() {
		return alive;
	}

} // namespace game 