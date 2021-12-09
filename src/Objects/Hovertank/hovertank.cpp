#include "Objects/Hovertank/hovertank.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <time.h>

#include "Control/game.h"

namespace game {
	using namespace Math;

	HoverTank::HoverTank(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
    forward_ = glm::vec3(0, 0, 1); // consider taking this in as a parameter
		turret_ = nullptr;
		velocity_ = glm::vec3(0);
		acceleration_ = glm::vec3(0);
		maxVelocity_ = 20.0f;
		speedMultiple_ = 1.0f; // used to change speed effects on the tanks (eg. going through mud)
		speedEffectMultiple_ = 1.0f; // used for speed effects (eg. mud, boost)
	}

	HoverTank::~HoverTank() {}

	void HoverTank::Update(void) {
		std::string posString = std::to_string(GetPosition().x) + ", " + std::to_string(GetPosition().y) + ", " + std::to_string(GetPosition().z);
		((HUD*)Game::GetInstance().GetMenu(MenuType::HUD))->ActivateTooltip(posString, 0.25f);

		// Update tank movement if game is not in freeroam
		if (!Game::GetInstance().GetFreeroam()) {
			if (!scanner_->IsScanning()) {
				motionControl();
				turretControl();
			}
			shootingControl();

			// Check for collision
			objectCollision();
			terrainCollision();
		}
	}

	void HoverTank::shootingControl() {
		// shoot currently selected projectile
		if (Input::getMouseButton(INPUT_MOUSE_BUTTON_1)) {
			Projectile* proj = turret_->UseSelectedAbility(GetPosition(), GetForward());
		}
	}

	void HoverTank::turretControl() {
		float rotAngle = -Input::getAxisMouse(INPUT_AXIS_HORIZONTAL);
		if(rotAngle != 0) {
			glm::quat rot = glm::angleAxis(((glm::pi<float>() * rotAngle) / 180) * Time::GetDeltaTime(), GetUp());
			turret_->Rotate(rot);
		}
	}

	void HoverTank::motionControl() {
		static float rot_factor = (glm::pi<float>() * 60) / 180;
		static float speedIncrease = 1.0f;
		static float gravity = 2.0f;
		static float friction = 0.35f;

		// Accelerate due to gravity
		acceleration_.y -= gravity;

		// Accelerate due to frition
		if (velocity_.x != 0.0f || velocity_.z != 0) {
			if (glm::length(glm::vec3(velocity_.x, 0.0f, velocity_.z)) < friction) {
				// Stop motion in the x and z direction if velocity is smaller than the force of friction
				velocity_ = glm::vec3(0.0f, velocity_.y, 0.0f);
			} else {
				// Add friction force in the same direction as velocity
				acceleration_ += glm::normalize(glm::vec3(velocity_.x, 0.0f, velocity_.z)) * -friction;
			}
		}

		// Accelerate forward/backward
		if (Input::getKey(INPUT_KEY_W)) {
			acceleration_ += GetForward() * speedIncrease;
		}
		if (Input::getKey(INPUT_KEY_S)) {
			acceleration_ -= GetForward() * speedIncrease;
		}

		// Rotate left/right
		if (Input::getKey(INPUT_KEY_A)) {
			glm::quat rotation = glm::angleAxis(rot_factor * Time::GetDeltaTime(), GetUp());
			Rotate(rotation);
		}
		if (Input::getKey(INPUT_KEY_D)) {
			glm::quat rotation = glm::angleAxis(-rot_factor * Time::GetDeltaTime(), GetUp());
			Rotate(rotation);
		}

		// Clamp x and z velocity to max vehicle speed
		float magnitude = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.z, 2.0f));
		if (magnitude > maxVelocity_) {
			velocity_.x = (velocity_.x / magnitude) * maxVelocity_;
			velocity_.z = (velocity_.z / magnitude) * maxVelocity_;
		}
		// Clamp y velocity to max gravity speed
		velocity_.y = glm::clamp(velocity_.y, -75.0f, 50.0f);

		velocity_ += acceleration_; // Increment velocity by acceleration
		acceleration_ = glm::vec3(0); // Reset acceleration
		Translate(velocity_ * speedMultiple_ * speedEffectMultiple_ * Time::GetDeltaTime()); // Translate by velocity
	}

	void HoverTank::objectCollision() {
		std::vector<Artifact*> artifacts = Game::GetInstance().GetArtifacts();
		std::vector<CarePackage*> carePackages = Game::GetInstance().GetCarePackages();

		for (int i = 0; i < artifacts.size(); i++) {
			if (Math::isCollidingSphereToSphere(GetCollider(), artifacts[i]->GetCollider())) {
				// Get direction vector from tank's position to objects positions (normalized).
				Vector3 direction = glm::normalize(GetPosition() - artifacts[i]->GetPosition());
				// Get magnitude float from ((tank's collider radius + object's collider radius) - (distance between tank and object))
				float magnitude = (GetCollider().radius + artifacts[i]->GetCollider().radius) - glm::distance(GetPosition(), artifacts[i]->GetPosition());
				// Translate tank by direction vector times magnitude
				Translate(direction * magnitude);
			}
		}
		for (int i = 0; i < carePackages.size(); i++) {
			if (Math::isCollidingSphereToSphere(GetCollider(), carePackages[i]->GetCollider())) {
				// Get direction vector from tank's position to objects positions (normalized).
				Vector3 direction = glm::normalize(GetPosition() - carePackages[i]->GetPosition());
				// Get magnitude float from ((tank's collider radius + object's collider radius) - (distance between tank and object))
				float magnitude = (GetCollider().radius + carePackages[i]->GetCollider().radius) - glm::distance(GetPosition(), carePackages[i]->GetPosition());
				// Translate tank by direction vector times magnitude
				Translate(direction * magnitude);
			}
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

	SphereCollider HoverTank::GetCollider(void) const {
		return {GetPosition(), 2.5f};
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

	void HoverTank::SetSpeedEffectMultiple(float multiple)
	{
		speedEffectMultiple_ = multiple;
	}

	void HoverTank::IncreaseSpeedMultiple(float increase)
	{
		speedMultiple_ += increase;
	}
}