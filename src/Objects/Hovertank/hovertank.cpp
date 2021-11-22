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
    forward_ = glm::vec3(0, 0, 1); // consider taking this in as a parameter
		turret_ = nullptr;
		velocity_ = glm::vec3(0);
		acceleration_ = glm::vec3(0);
		maxVelocity_ = 30.0f;
		speedMultiple_ = 1.0f; // used to change speed effects on the tanks (eg. going through mud)
		SetCollisionBox(glm::vec3(2.5f, 2.5f, 2.5));
	}

	HoverTank::~HoverTank() {}

	void HoverTank::Update(void) {
		// Update tank movement if game is not in freeroam
		if (!Game::GetInstance().GetFreeroam()) {
			if (!scanner_->IsScanning()) {
				motionControl();
			}
			shootingControl();
		}
    
		// Check for terrain collision
		terrainCollision();
	}

	void HoverTank::shootingControl() {
		// shoot currently selected projectile
		if (Input::getKey(INPUT_KEY_SPACE)) {
			Projectile* proj = turret_->UseSelectedAbility(GetPosition(), GetForward());
		}
		if(Input::getKey(INPUT_KEY_Q)) { // left
			glm::quat rot = glm::angleAxis(((glm::pi<float>() * 60) / 180) * Time::GetDeltaTime(), GetUp());
			turret_->Rotate(rot);
		}
		if (Input::getKey(INPUT_KEY_E)) { // right
			glm::quat rot = glm::angleAxis(-((glm::pi<float>() * 60) / 180) * Time::GetDeltaTime(), GetUp());
			turret_->Rotate(rot);
		}
	}

	void HoverTank::motionControl() {
		static float rot_factor = (glm::pi<float>() * 60) / 180;
		static float speedIncrease = 2.0f;
		static float gravity = 1.0f;
		static float friction = 0.25f;

		// Accelerate due to gravity
		acceleration_.y -= gravity;

		// Accelerate due to frition
		if (velocity_.x != 0.0f || velocity_.z != 0) {
			// Add friction force in the same direction as velocity
			acceleration_ += glm::normalize(glm::vec3(velocity_.x, 0.0f, velocity_.z)) * -friction;
		}

		// Accelerate forward/backward
		if (Input::getKey(INPUT_KEY_W)) {
			acceleration_ += GetForward() * speedIncrease;
		}
		if (Input::getKey(INPUT_KEY_S)) {
			acceleration_ -= GetForward() * speedIncrease;
		}
		// Accelerate left/right
		if (Input::getKey(INPUT_KEY_A)) {
			acceleration_ -= GetRight() * speedIncrease;
		}
		if (Input::getKey(INPUT_KEY_D)) {
			acceleration_ += GetRight() * speedIncrease;
		}
		
		// Clamp to max speed
		float magnitude = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.y, 2.0f) + pow(velocity_.z, 2.0f));
		if (magnitude > maxVelocity_) {
			velocity_ /= magnitude;
			velocity_ *= maxVelocity_;
		}

		velocity_ += acceleration_; // Increment velocity by acceleration
		acceleration_ = glm::vec3(0); // Reset acceleration
		Translate(velocity_ * speedMultiple_ * Time::GetDeltaTime()); // Translate by velocity

		// Rotate yaw
		if (Input::getKey(INPUT_KEY_LEFT)) {
			glm::quat rotation = glm::angleAxis(rot_factor * Time::GetDeltaTime(), GetUp());
			Rotate(rotation);
		}
		if (Input::getKey(INPUT_KEY_RIGHT)) {
			glm::quat rotation = glm::angleAxis(-rot_factor * Time::GetDeltaTime(), GetUp());
			Rotate(rotation);
		}
	}

	void HoverTank::terrainCollision() { 
		Terrain* terrain = Game::GetInstance().GetTerrain();
		glm::vec3 position = this->GetPosition();

		glm::vec3 hitpoint; // return value for terrain collision
		if (terrain->Collision(position, 1, hitpoint)) {
			hitpoint.y += 2.0f; // add height of tank to hitpoint
			if (position.y <= hitpoint.y) {
				Translate(glm::vec3(0, hitpoint.y - position.y, 0));
				velocity_.y = 0;
			}
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

	glm::vec3 HoverTank::GetVelocity(void) {
		return velocity_;
	}

	float HoverTank::GetStrength() {
		return strength;
	}

	HoverTankTurret* HoverTank::GetTurret() {
		return turret_;
	}

	// Takes a normalized direction vector and a force value
	void HoverTank::AddForce(glm::vec3 direction, float force) {
		acceleration_ += direction * force;
	}

	void HoverTank::SetStrength(float newStrength) {
		strength = newStrength;
	}

	void HoverTank::SetTurret(HoverTankTurret* turret) {
		turret_ = turret;
	}

	void HoverTank::SetScanner(Scanner* scanner) {
		scanner_ = scanner;
	}
	
	void HoverTank::SetSpeedMultiple(float multiple) {
		speedMultiple_ = multiple;
	}

	void HoverTank::IncreaseMaxSpeed(float increase)
	{
		maxVelocity_ += increase;
	}
}