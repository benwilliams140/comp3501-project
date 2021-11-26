#include "Objects/EnvironmentObject.h"
#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include <control/game.h>
#include <control/mathematics.h>
#include "Objects/Hovertank/Abilities/ability.h"
#include "Objects/Projectiles/projectile.h"

#define MAX_INST_GROUPS 4
#define MAX_POSITIONS 250

namespace game {
	using namespace Math;

	EnvironmentObject::EnvironmentObject(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		instanced_ = true;
		instGroupID_ = 0;
		colliderRadius_ = 1.0f;
		tank_ = Game::GetInstance().GetPlayer()->GetTank();
	}

	EnvironmentObject::~EnvironmentObject() {
		delete[] positions_;
	}

	void EnvironmentObject::Update(void) {
		HovertankCollision();
		ProjectileCollision();
	}

	void EnvironmentObject::HovertankCollision() {
		for (int i = 0; i < positionsSize_; i++) {
			if (Math::isCollidingSphereToSphere(tank_->GetCollider(), {positions_[i], colliderRadius_})) {
				// TODO - move tank away from object and remove velocity in that direction
			}
		}
	}

	void EnvironmentObject::ProjectileCollision() {
		std::vector<Ability*> abilities = tank_->GetTurret()->GetAbilities();
		std::vector<Projectile*> projectiles;

		//have it loop through all player projectiles with evironment objects
		for (int i = 0; i < abilities.size(); i++) {
			projectiles = abilities[i]->GetProjectiles();
			for (int j = 0; j < projectiles.size(); j++) {
				for (int k = 0; k < positionsSize_; k++) {
					//if they collide seet projectile lifespan to 0 to be destroyed
					if (Math::isCollidingSphereToSphere(projectiles[j]->GetCollider(), { positions_[k], colliderRadius_ })) {
						projectiles[j]->SetLifespan(0.0f);
					}
				}
			}
		}
		//have it loop through all enemy projectiles with evironment objects
		projectiles = Game::GetInstance().GetEnemyProjectiles();
		for (int n = 0; n < projectiles.size(); n++) {
			for (int m = 0; m < positionsSize_; m++) {
				//if they collide seet projectile lifespan to 0 to be destroyed
				if (Math::isCollidingSphereToSphere(projectiles[n]->GetCollider(), { positions_[m], colliderRadius_ })) {
					projectiles[n]->SetLifespan(0.0f);
				}
			}
		}
		
	}

	void EnvironmentObject::InitPositions(int seed, int amount) {
		Terrain* terrain = Game::GetInstance().GetTerrain();
		positions_ = new Vector3[amount];
		instanceAmount_ = positionsSize_ = amount;

		srand(seed);
		for (int i = 0; i < amount; i++) {
			float x = randRangeFloat(-450, 450);
			float z = randRangeFloat(-450, 450);
			float y = terrain->GetHeightAt(x, z);
			positions_[i] = glm::vec3(x, y, z);
		}
	}

	void EnvironmentObject::InitShaderUniform(GLuint program) {
		GLint positions_var = glGetUniformLocation(program, std::string("positions[" + std::to_string(instGroupID_ * MAX_POSITIONS) + "]").c_str());
		glUniform3fv(positions_var, positionsSize_, (const GLfloat*)positions_);
	}

	void EnvironmentObject::UpdateShaderUniform(GLuint program) {
		GLint instGroupID_var = glGetUniformLocation(program, "groupID");
		glUniform1i(instGroupID_var, (int)instGroupID_);
	}

	glm::vec3* EnvironmentObject::GetPositions() {
		return positions_;
	}

	size_t EnvironmentObject::GetPositionsSize(void) const {
		return positionsSize_;
	}

	void EnvironmentObject::SetPositions(Vector3** listOfPos, size_t sizeOfPos) {
		positions_ = *listOfPos;
		positionsSize_ = sizeOfPos;
	}

	unsigned int EnvironmentObject::GetInstanceGroupID(void) const {
		return instGroupID_;
	}

	void EnvironmentObject::SetInstanceGroupID(unsigned int id) {
		if(id < MAX_INST_GROUPS) instGroupID_ = id;
	}

	void EnvironmentObject::SetColliderRadius(float radius) {
		if(radius >= 0) colliderRadius_ = radius;
	}
}