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
    forward_ = glm::vec3(0, 0, 1); // consider taking this in as a parameter
		turret_ = nullptr;
		//forward_ = glm::vec3(0, 0, -1); // consider taking this in as a parameter
		fwdSpeed_ = sideSpeed_ = 0;
		maxSpeed_ = 1.0f;
	}

	HoverTank::~HoverTank() {}

	void HoverTank::Update(void) {
		// Update tank movement
		motionControl();
    //shootingControl();
    
		// Check for terrain collision
		terrainCollision();
	}
  
  /*void HoverTank::shootingControl() {
    // shoot currently selected projectile
    if (Input::getKey(INPUT_KEY_SPACE)) {
        Resource* geom = GetResource("Cube");
        Resource* mat = GetResource("Simple");
        Resource* tex = GetResource("RockyTexture");
        Projectile* outProj = nullptr;
        turret_->UseSelectedAbility(&outProj, player_->GetTank()->GetForward(), geom, mat, tex);
        if (outProj) {
            outProj->SetPosition(player_->GetTank()->GetPosition());
            outProj->Scale(glm::vec3(0.5f));
            scene_.AddNode(outProj);
        }
    } 
  }*/

	void HoverTank::motionControl() {
		float rot_factor = glm::pi<float>() / 180;
		float trans_factor = 0.25f;
		float friction = 0.01f;
		
		// Reduce speed by friction
		if (fwdSpeed_ != 0) {
			if (fwdSpeed_ > friction) { fwdSpeed_ -= friction; } 
			else if (fwdSpeed_ < -friction) { fwdSpeed_ += friction; } 
			else { fwdSpeed_ = 0; }
		}
		if (sideSpeed_ != 0) {
			if (sideSpeed_ > friction) { sideSpeed_ -= friction; } 
			else if (sideSpeed_ < -friction) { sideSpeed_ += friction; } 
			else { sideSpeed_ = 0; }
		}

		// Translate forward/backward
		if (Input::getKey(INPUT_KEY_W)) {
			fwdSpeed_ += 0.1f;
		}
		if (Input::getKey(INPUT_KEY_S)) {
			fwdSpeed_ -= 0.1f;
		}
		// Translate left/right
		if (Input::getKey(INPUT_KEY_A)) {
			sideSpeed_ -= 0.1f;
		}
		if (Input::getKey(INPUT_KEY_D)) {
			sideSpeed_ += 0.1f;
		}
		
		// Clamp to max speed
		if (fwdSpeed_ > maxSpeed_) fwdSpeed_ = maxSpeed_;
		if (fwdSpeed_ < -maxSpeed_) fwdSpeed_ = -maxSpeed_;
		if (sideSpeed_ > maxSpeed_) sideSpeed_ = maxSpeed_;
		if (sideSpeed_ < -maxSpeed_) sideSpeed_ = -maxSpeed_;

		// Translate by gravity
		Translate(glm::vec3(0, -0.35f, 0));
		// Translate by speed
		Translate(GetForward() * fwdSpeed_);
		Translate(GetRight() * sideSpeed_);

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

	glm::vec3 HoverTank::GetVelocity(void) {
		return velocity;
	}

	float HoverTank::GetStrength() {
		return strength;
	}

	HoverTankTurret* HoverTank::GetTurret() {
		return turret_;
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
}