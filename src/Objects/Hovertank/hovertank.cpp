#include "Objects/Hovertank/hovertank.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	HoverTank::HoverTank(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		velocity = glm::vec3(0, 0, 0);
		forward_ = glm::vec3(0, 0, 1); // consider taking this in as a parameter
		colliderBox_x = 10;
		colliderBox_y = 10;
		colliderBox_z = 10;
	}

	HoverTank::~HoverTank() {
	}

	glm::vec3 HoverTank::GetForward(void) {
		return GetOrientation() * glm::normalize(forward_);
	}

	glm::vec3 HoverTank::GetRight(void) {
		return glm::normalize(glm::cross(GetForward(), GetUp()));
	}

	glm::vec3 HoverTank::GetUp(void) {
		return GetOrientation() * glm::normalize(glm::vec3(0, 1, 0)); // hardcoded up vector for now
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

	}

	void HoverTank::movementControl() {}

	bool HoverTank::collisionDetection() { return false; }

}