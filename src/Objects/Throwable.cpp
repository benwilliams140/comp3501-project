#include "Objects/Throwable.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	Throwable::Throwable(const std::string name, const Resource* geometry, const Resource* material, glm::vec3 vel) : SceneNode(name, geometry, material) {
		velocity = vel;
		alive = true;
		lifeSpan = 500;
		colliderBox_x = 10;
		colliderBox_y = 10;
		colliderBox_z = 10;
	}


	Throwable::~Throwable() {
	}


	glm::quat Throwable::GetAngM(void) const {

		return angm_;
	}


	void Throwable::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void Throwable::Update(void) {
		//update position
		SetPosition(GetPosition() + velocity);

		//lower lifespan
		if (lifeSpan > 0) {
			lifeSpan--;
		}
		else {
			alive = false;
		}

		//update velocity so it will have a parabolic trajectory
		velocity -= glm::vec3(0, 0.01f, 0);
	}

	bool Throwable::isAlive() {
		return alive;
	}

} // namespace game 