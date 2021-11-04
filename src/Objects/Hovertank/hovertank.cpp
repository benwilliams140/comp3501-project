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
		turret_ = nullptr;
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

	float HoverTank::GetSpeed(void) {
		return speed;
	}

	glm::vec3 HoverTank::GetVelocity(void) {
		return velocity;
	}

	float HoverTank::GetStrength() {
		return strength;
	}

	HoverTankTurret* HoverTank::GetTurret() {
		return turret_;
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

	void HoverTank::SetTurret(HoverTankTurret* turret) {
		turret_ = turret;
	}

	void HoverTank::Update(void) {

	}

	void HoverTank::movementControl() {}

	bool HoverTank::collisionDetection() { return false; }

}