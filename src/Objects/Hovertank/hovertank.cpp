#include "Objects/Hovertank/hovertank.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

#include "Control/game.h"

namespace game {

	HoverTank::HoverTank(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		velocity = glm::vec3(0, 0, 0);
		forward_ = glm::vec3(0, 0, -1); // consider taking this in as a parameter
		colliderBox_x = 10;
		colliderBox_y = 10;
		colliderBox_z = 10;
	}

	HoverTank::~HoverTank() {}

	void HoverTank::Update(void) {
		// Update tank movement
		motionControl();
		// Check for terrain collision
		terrainCollision();
	}

	void HoverTank::motionControl() {
		float rot_factor = glm::pi<float>() / 180;
		float trans_factor = 0.25f;

		// Translate by gravity
		Translate(glm::vec3(0, -0.35f, 0));

		// Translate forward/backward
		if (Input::getKey(INPUT_KEY_W)) {
			Translate(GetForward() * trans_factor);
		}
		if (Input::getKey(INPUT_KEY_S)) {
			Translate(-GetForward() * trans_factor);
		}
		// Translate left/right
		if (Input::getKey(INPUT_KEY_A)) {
			Translate(-GetRight() * trans_factor);
		}
		if (Input::getKey(INPUT_KEY_D)) {
			Translate(GetRight() * trans_factor);
		}
		// Rotate yaw
		if (Input::getKey(INPUT_KEY_LEFT)) {
			glm::quat rotation = glm::angleAxis(rot_factor, GetUp());
			Rotate(rotation);
		}
		if (Input::getKey(INPUT_KEY_RIGHT)) {
			glm::quat rotation = glm::angleAxis(-rot_factor, GetUp());
			Rotate(rotation);
		}
	}

	void HoverTank::terrainCollision() { 
		Terrain* terrain = Game::GetInstance().GetTerrain();
		glm::vec3 position = this->GetPosition();

		glm::vec3 hitpoint; // return value for terrain collision
		if (terrain->Collision(position, 1, hitpoint)) {
			hitpoint.y += 1.0f; // add height of tank to hitpoint
			Translate(glm::vec3(0, hitpoint.y - position.y, 0));
		}
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
}