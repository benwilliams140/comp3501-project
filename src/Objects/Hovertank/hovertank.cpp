#include "Objects/Hovertank/hovertank.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	HoverTank::HoverTank(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {
		velocity = glm::vec3(0, 0, 0);
		colliderBox_x = 10;
		colliderBox_y = 10;
		colliderBox_z = 10;
	}


	HoverTank::~HoverTank() {
	}


	glm::quat HoverTank::GetAngM(void) const {

		return angm_;
	}


	float HoverTank::GetSpeed(void) {

		return speed;
	}

	glm::vec3 HoverTank::GetVelocity(void) {

		return velocity;
	}

	

	float HoverTank::GetStrength() {
		return strength;
	}

	void HoverTank::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void HoverTank::SetSpeed(float newSpeed) {

		speed = newSpeed;
	}

	void HoverTank::SetVelocity(glm::vec3 newVelocity) {

		velocity = newVelocity;
	}

	void HoverTank::SetStrength(float newStrength) {

		strength = newStrength;
	}


	void HoverTank::Update(void) {

		Rotate(angm_);
	}

	void HoverTank::movementControl() {}

	bool HoverTank::collisionDetection() { return false; }

}